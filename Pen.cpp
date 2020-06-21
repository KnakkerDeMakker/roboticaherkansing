#include "Pen.h"

Pen::Pen(Shape *X, Shape *Y, ServoDriver *Z)
	: Square({ X->GetOrig().X , Y->GetOrig().Y }, 0.05f), PivotX(X), PivotY(Y), servo(Z), old(GetOrig()), trace(std::vector<Line>()) {};


void Pen::Routine(float time) {
	SetOrig({ PivotX->GetOrig().X, PivotY->GetOrig().Y });

}

void Pen::Draw() {
	Square::Draw();
	if (servo->IsUp()) {
		sometimes++;
		for (auto& line : trace) {
			glBegin(GL_LINES);
			glColor3f(0, 0, 1);
			glVertex2f(line.p1.X, line.p1.Y);
			glVertex2f(line.p2.X, line.p2.Y);
			glEnd();
		}
		if (sometimes % 3 == 0) {
			trace.push_back({ old, GetOrig() });
			sometimes = 0;
		}
	}
	if (sometimes % 3 == 0) {
		old = GetOrig();
	}
}
