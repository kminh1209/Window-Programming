#include "CCircle.h"
CCircle::CCircle(HDC hdc, int l, int t, int r, int b)
	:Shape(hdc, l, t, r, b)
{
}
void CCircle::repaint() {
	::Ellipse(hdc_, left_, top_, right_, bottom_);
}
