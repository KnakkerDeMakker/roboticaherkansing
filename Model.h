#include "Dynamic.h"
#include "Drawable.h"
#include <math.h>


#define M_PI            3.14159265358979323846
#define CIRCLEDEF		200
#define TRIDEF			200
#define POINTTIME		1000
#define RADIUSTIME		500


struct TaskSet {
	std::queue<Task> X = std::queue<Task>();
	std::queue<Task> Y = std::queue<Task>();
	std::queue<Task> Z = std::queue<Task>();
};

class Model
{
private:
	Square *xPivot, *yPivot;
	MotorDriver *XDriver, *YDriver;
	ServoDriver *servo;
	Pen *pen;
	bool initialized = false;

public:
	int vorm;
	Point2 pos;
	float rad;
	Model();
	~Model();
	std::vector<Dynamic *> getDynamicObjects();
	std::vector<Shape *> getDrawables();
	void Init();

private:
	TaskSet DrawCircle(float radius, float time, Point2 pos);
	TaskSet DrawTriangle(float radius, float time, Point2 pos);
	TaskSet DrawSquare(float radius, float time, Point2 pos);
	TaskSet DrawPenta(float radius, float time, Point2 pos);
	TaskSet DrawHexa(float radius, float time, Point2 pos);
};

bool test_Model();
