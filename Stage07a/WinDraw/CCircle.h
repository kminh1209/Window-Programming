#pragma once
#include "Shape.h"
class CCircle :
	public Shape
{
public:
	CCircle(HDC, int, int, int, int);
	void repaint();
};

