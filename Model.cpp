#include "Model.h"

Model::Model()
	: XDriver(nullptr), YDriver(nullptr), pen(nullptr) {}

Model::~Model()
{
	delete XDriver, YDriver, pen;
}

std::vector<Dynamic *> Model::getDynamicObjects()
{
	if (initialized)
	{
		std::vector<Dynamic *> out;
		out.push_back(XDriver);
		out.push_back(YDriver);
		out.push_back(pen);
		out.push_back(servo);
		return out;
	}
	else
	{
		throw "Model uninitialized";
		return std::vector<Dynamic *>();
	}
}

void Model::Init()
{
	xPivot = new Square({ -0.5f, 0.5f }, 0.05f);
	yPivot = new Square({ -0.5f, 0.5f }, 0.05f);
	XDriver = new MotorDriver(*xPivot, true);
	YDriver = new MotorDriver(*yPivot, false);

	servo = new ServoDriver();
	pen = new Pen(xPivot, yPivot, servo);

	//v0.0.3: Curves!
	if (vorm == 1) {
		auto Triangle = DrawTriangle(0.3f,3000.0f, pos);
		XDriver->AddTask(Triangle.X);
		YDriver->AddTask(Triangle.Y);
		servo->AddTask(Triangle.Z);
	}
	else if (vorm == 2) {
		auto Square = DrawSquare(0.3f, 3000.0f, pos);
		XDriver->AddTask(Square.X);
		YDriver->AddTask(Square.Y);
		servo->AddTask(Square.Z);
	}
	else if (vorm == 3) {
		auto Penta = DrawPenta(0.3f, 3000.0f, pos);
		XDriver->AddTask(Penta.X);
		YDriver->AddTask(Penta.Y);
		servo->AddTask(Penta.Z);
	}
	else if (vorm == 4) {
		auto Hexa = DrawHexa(0.3f, 3000.0f, pos);
		XDriver->AddTask(Hexa.X);
		YDriver->AddTask(Hexa.Y);
		servo->AddTask(Hexa.Z);
	}
	else if (vorm == 5) {
		rad = rad / 125.0;
		auto Circle = DrawCircle(rad, 3000.0f, pos);
		XDriver->AddTask(Circle.X);
		YDriver->AddTask(Circle.Y);
		servo->AddTask(Circle.Z);
	}
	initialized = true;
}

TaskSet Model::DrawTriangle(float radius, float time, Point2 pos) {
	TaskSet out;
	Task task;

	//Go to position
	task.Time = POINTTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Go to bottom of triangle
	task.Time = RADIUSTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y - radius;
	out.Y.push(task);

	//Handle Z
	task.Time = POINTTIME + RADIUSTIME;
	task.Dest = 1;
	out.Z.push(task);
	task.Time = time + POINTTIME + RADIUSTIME * 1.82f;
	task.Dest = -1;
	out.Z.push(task);


	//Divide time over segments;
	task.Time = time / TRIDEF;

	//Draw triangle
	task.Dest = pos.X + radius;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	task.Dest = pos.X - radius;
	out.X.push(task);
	task.Dest = pos.Y + (radius * 2);
	out.Y.push(task);

	task.Dest = pos.X - radius;
	out.X.push(task);
	task.Dest = pos.Y - (radius * 2);
	out.Y.push(task);

	task.Dest = pos.X + radius;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Go back to pos
	task.Time = RADIUSTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	return out;
}

TaskSet Model::DrawSquare(float radius, float time, Point2 pos) {
	TaskSet out;
	Task task;

	//Go to position
	task.Time = POINTTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Go to bottom of rectangle
	task.Time = RADIUSTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y - radius;
	out.Y.push(task);

	//Handle Z
	task.Time = POINTTIME + RADIUSTIME;
	task.Dest = 1;
	out.Z.push(task);
	task.Time = time + POINTTIME + RADIUSTIME * 1.82f;
	task.Dest = -1;
	out.Z.push(task);

	//Divide time over segments;
	task.Time = time / TRIDEF;

	//Draw Rectangle
	task.Dest = pos.X + radius;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y + (radius * 2);
	out.Y.push(task);

	task.Dest = pos.X - (radius * 2);
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y - (rad * 2);
	out.Y.push(task);

	task.Dest = pos.X + rad;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Go back to pos
	task.Time = RADIUSTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	return out;
}

TaskSet Model::DrawPenta(float radius, float time, Point2 pos) {
	TaskSet out;
	Task task;

	//Go to position
	task.Time = POINTTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Go to bottom of penta
	task.Time = RADIUSTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y - radius;
	out.Y.push(task);

	//Handle Z
	task.Time = POINTTIME + RADIUSTIME;
	task.Dest = 1;
	out.Z.push(task);
	task.Time = time + POINTTIME + RADIUSTIME * 1.82f;
	task.Dest = -1;
	out.Z.push(task);

	//Divide time over segments;
	task.Time = time / TRIDEF;

	//DrawPenta
	task.Dest = pos.X + (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	task.Dest = pos.X + (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y + rad;
	out.Y.push(task);

	task.Dest = pos.X - rad;
	out.X.push(task);
	task.Dest = pos.Y + rad;
	out.Y.push(task);

	task.Dest = pos.X - rad;
	out.X.push(task);
	task.Dest = pos.Y - rad;
	out.Y.push(task);

	task.Dest = pos.X + (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y - rad;
	out.Y.push(task);

	task.Dest = pos.X + (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Go back to pos
	task.Time = RADIUSTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	return out;
}

TaskSet Model::DrawHexa(float radius, float time, Point2 pos) {
	TaskSet out;
	Task task;

	//Go to position
	task.Time = POINTTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Go to bottom of hexa
	task.Time = RADIUSTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y - radius;
	out.Y.push(task);

	//Handle Z
	task.Time = POINTTIME + RADIUSTIME;
	task.Dest = 1;
	out.Z.push(task);
	task.Time = time + POINTTIME + RADIUSTIME * 1.82f;
	task.Dest = -1;
	out.Z.push(task);

	//Divide time over segments;
	task.Time = time / TRIDEF;

	//DrawHexa
	task.Dest = pos.X + (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	task.Dest = pos.X + (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y + rad;
	out.Y.push(task);

	task.Dest = pos.X - (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y + rad;
	out.Y.push(task);

	task.Dest = pos.X - rad;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	task.Dest = pos.X - (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y - rad;
	out.Y.push(task);

	task.Dest = pos.X + (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y - rad;
	out.Y.push(task);

	task.Dest = pos.X + (rad / 2);
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Go back to pos
	task.Time = RADIUSTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	return out;
}

TaskSet Model::DrawCircle(float radius, float time, Point2 pos) {
	TaskSet out;
	Task task;

	//Go to position
	task.Time = POINTTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Go to right side of circle
	task.Time = RADIUSTIME;
	task.Dest = pos.X + radius;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	//Handle Z
	task.Time = POINTTIME + RADIUSTIME;
	task.Dest = 1;
	out.Z.push(task);
	task.Time = time + POINTTIME + RADIUSTIME * 1.82f;
	task.Dest = -1;
	out.Z.push(task);


	//Divide time over segments;
	task.Time = time / CIRCLEDEF;

	for (int i = 0; i < CIRCLEDEF; i++) {
		auto theta = (2 * M_PI) / CIRCLEDEF * i;
		task.Dest = float(cos(theta) * radius + pos.X);
		out.X.push(task);
		task.Dest = float(sin(theta) * radius + pos.Y);
		out.Y.push(task);
	}

	//Go back to pos
	task.Time = RADIUSTIME;
	task.Dest = pos.X;
	out.X.push(task);
	task.Dest = pos.Y;
	out.Y.push(task);

	return out;
}

std::vector<Shape *> Model::getDrawables()
{
	if (initialized)
	{
		std::vector<Shape *> out = std::vector<Shape *>();
		out.push_back(yPivot);
		out.push_back(xPivot);
		out.push_back(pen);
		return out;
	}
	else
	{
		throw "Model is not initialized.";
		return std::vector<Shape *>();
	}
}

bool test_Model()
{
	try
	{
	}
	catch (const char* e)
	{
		printf("%s\n", e);
		return false;
	}
	return true;
}