#include "Point.h"

Point2::Point2(float x, float y)
	: X(x), Y(y) {}

Point2 Point2::Add(float x, float y)
{
	return Point2(X + x, Y + y);
}

bool test_Point()
{
	try
	{
		Point2 p(3, 0);

		//Test Add
		if (p.Add(5, 4).X != 8 || p.Add(0, -2).Y != -2)
			throw "POINT ERROR (ADD)";
		return true;
	}
	catch (const char *e)
	{
		return false;
	}
}
