#pragma once
#include "Windows.h"
class Shapestuff
{
public:
	Shapestuff(HDC, int, int, int, int);
	virtual void repaint() = 0;
	bool iscontain(int l, int t, int r, int b);
	bool belongs(int x, int y);
	void move(int, int);
	int getLeft();
	int getTop();
	int getRight();
	int getBottom();
protected:
	int left_, right_, top_, bottom_;
	HDC hdc_;
};

