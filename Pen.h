#pragma once
#include "Square.h"
#include "ServoDriver.h"
#include "Dynamic.h"
#include <vector>
#include <iostream>

class Pen : public Square, public Dynamic
{
private:
	int sometimes;
	Point2 old;
	Shape *PivotX, *PivotY;
	ServoDriver *servo;
	std::vector<Line> trace;

public:
	Pen(Shape *X, Shape *Y, ServoDriver *servo);
	void Routine(float) override;
	void Draw() override;
};
