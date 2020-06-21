#include "Shape.h"

void Shape::Move(float x, float y)
{
	SetOrig({ GetOrig().X + x, GetOrig().Y + y });
}

void Shape::SetOrig(const Point2 &pos)
{
	orig = pos;
}

Point2 Shape::GetOrig() const
{
	return orig;
}
