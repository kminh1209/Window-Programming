#pragma once
#include "Shape.h"
class CRectangle :
	public Shape
{
public:
	CRectangle(HDC, int, int, int, int);
	void repaint();
};

