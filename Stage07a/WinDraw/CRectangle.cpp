#include "CRectangle.h"
CRectangle::CRectangle(HDC hdc, int l, int t, int r, int b)
	:Shape(hdc, l, t, r, b) {

}

void CRectangle::repaint() {
	OutputDebugStringW(L"사각형 리페인트\n");
	::Rectangle(hdc_, left_, top_, right_, bottom_);
}

