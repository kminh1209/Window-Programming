#include "Shape.h"
Shapestuff::Shapestuff(HDC hdc, int l, int t, int r, int b)
	: hdc_(hdc), left_(l), top_(t), right_(r), bottom_(b)
{
	// Empty
}

void Shapestuff::move(int r, int b) {
	left_ += r;
	right_ += r;
	top_ += b;
	bottom_ += b;
}
bool Shapestuff::iscontain(int l, int t, int r, int b) {
	int left, right, top, bottom; // 비교를 위해 크기순으로 정렬
	left = min(left_, right_); 
	top = min(top_, bottom_);
	right = max(left_, right_);
	bottom = max(top_, bottom_);

	return (l < left && right < r && t < top && bottom < b);
}

bool Shapestuff::belongs(int x, int y) {
	int l, t, r, b; // 비교를 위해 크기순으로 정렬
	l = min(left_, right_); 
	t = min(top_, bottom_);
	r = max(left_, right_); 
	b = max(top_, bottom_);

	return (l < x && x < r && t < y && y < b);
}

int Shapestuff::getLeft() {
	return left_;
}
int Shapestuff::getTop() {
	return top_;
}
int Shapestuff::getRight() {
	return right_;
}
int Shapestuff::getBottom() {
	return bottom_;
}
