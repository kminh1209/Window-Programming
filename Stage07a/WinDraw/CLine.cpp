#include "CLine.h"
CLine::CLine(HDC hdc, int l, int t, int r, int b)
	:Shape(hdc, l, t, r, b) {

}

void CLine::repaint() {
	::MoveToEx(hdc_, left_, top_, NULL);
	::LineTo(hdc_, right_, bottom_);
}

