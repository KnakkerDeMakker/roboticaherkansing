#pragma once
#include "Shape.h"

class Square : public Shape
{
	float size;

public:
	Square();
	/*
	 *  Creates square at pos, size is length of each side.
	 */
	Square(const Point2 &pos, float size);
	Point2 TL();
	Point2 TR();
	Point2 BL();
	Point2 BR();
	void Draw() override;
};

bool test_Square();
