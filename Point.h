#pragma once
class Point2
{

public:
	float X;
	float Y;

	Point2() {};
	Point2(float x, float y);

	Point2 Add(float x, float y);
};

bool test_Point();

struct Line {
	Point2 p1;
	Point2 p2;
};
