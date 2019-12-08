#pragma once
#include "Shapestuff.h"
class Shape:
	public Shapestuff
{
public:
	Shape(HDC, int, int, int, int);
	virtual void repaint() = 0;
protected:
	//int left_, right_, top_, bottom_;
	//HDC hdc_;
};

