#pragma once
#include "Point.h"
#include "Drawable.h"
#include "GL/glew.h"
#include "GL/glut.h"

class Shape : public Drawable
{
	Point2 orig;

public:
	//Abstract class
	virtual ~Shape() {};
	void Move(float x, float y);
	void SetOrig(const Point2 &pos);
	Point2 GetOrig() const;
};

bool test_Shape();
