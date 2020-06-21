#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Model.h"
#include "View.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <opencv2/core/utility.hpp> //libs voor opencv
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;
void simulationLoop();
void render();
int camera();
Point2 converter(int x, int y);
static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour);

Model* model;
View* view;

int main(int ac, char **ap)
{
	glutInit(&ac, ap);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("v0.0.2");
	model = new Model();
	camera(); //call camera function
	model->Init();
	view = new View(model);
	std::cout << "Initialization succesful.\n";
	glutIdleFunc(simulationLoop);
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}

void simulationLoop()
{
	view->Update();
	render();
}

void render()
{
	glClearColor(0, 0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	view->Draw();
	glFlush();
}

int camera()
{
	//cv::Mat src = cv::imread("polygon.png");
	cv::namedWindow("gray", cv::WINDOW_AUTOSIZE); //window for gray

	cv::VideoCapture cap; //opent je camera
	cap.open(0);

	if (!cap.isOpened())
	{
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}

	cv::Mat bgr_frame, grijs, canny; //maak frames

	for (int i = 0; i < 50; i++) //50 x 100 ms de tijd om cirkel voor camera te houden
	{
		cap >> bgr_frame; //capture wordt frame
		if (bgr_frame.empty()) break;

		cv::cvtColor(bgr_frame, grijs, cv::COLOR_BGR2GRAY); //convert color to gray
		cv::imshow("gray", grijs); //laat gray zien

		char c = cv::waitKey(10);
		if (c == 27) break;
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	imwrite("bruh.jpg", grijs);
	cv::Mat src = cv::imread("bruh.jpg");
	if (src.empty())
		return -1;

	 //Convert to grayscale
	//cv::Mat gray;
	//cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

	// Use Canny instead of threshold to catch squares with gradient shading
	cv::Mat bw;
	cv::Canny(src, bw, 0, 50, 5);

	// Find contours
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(bw.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<cv::Point> approx;
	cv::Mat dst = src.clone();

	for (int i = 0; i < contours.size(); i++)
	{
		// Approximate contour with accuracy proportional to the contour perimeter
		cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

		// skip small 
		if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
			continue;

		if (approx.size() == 3)
		{
			setLabel(dst, "TRI", contours[i]);    // Triangles
			model->vorm = 1;
		}
		else if (approx.size() >= 4 && approx.size() <= 6)
		{
			// Number of vertices of polygonal curve
			int vtc = approx.size();

			// Get the cosines of all corners
			std::vector<double> cos;
			for (int j = 2; j < vtc + 1; j++)
				cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));

			// Sort ascending the cosine values
			std::sort(cos.begin(), cos.end());

			// Get the lowest and the highest cosine
			double mincos = cos.front();
			double maxcos = cos.back();

			// Use the degrees obtained above and the number of vertices to determine the shape of the contour
			if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3) {
				setLabel(dst, "RECT", contours[i]);
				model->vorm = 2;
			}
			else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27) {
				setLabel(dst, "PENTA", contours[i]);
				model->vorm = 3;
			}
			else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45) {
				setLabel(dst, "HEXA", contours[i]);
				model->vorm = 4;
			}
		}
		else
		{
			// Detect and label circles
			double area = cv::contourArea(contours[i]);
			cv::Rect r = cv::boundingRect(contours[i]);
			model->rad = r.width / 2;


			if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 && std::abs(1 - (area / (CV_PI * std::pow(model->rad, 2)))) <= 0.2) {
				setLabel(dst, "CIR", contours[i]);
				model->vorm = 5;
			}
		}

	}

	//cv::imshow("src", src);
	cv::imshow("dst", dst);
	cap.release(); //camera uit
	return 0;
}

static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1 * dy2) / sqrt((dx1*dx1 + dy1 * dy1)*(dx2*dx2 + dy2 * dy2) + 1e-10);
}

void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
	cv::Rect r = cv::boundingRect(contour);

	cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255, 255, 255), cv::FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
	model->pos = converter(r.x, r.y);
}


Point2 converter(int x, int y) {
	Point2 out;

	out.X = (x / 200) - 1;
	out.Y = (y / 100) - 1;

	return out;
}

