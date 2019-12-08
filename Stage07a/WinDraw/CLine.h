#pragma once
#include "Shape.h"
class CLine :
	public Shape
{
public:
	CLine(HDC, int, int, int, int);
	void repaint();
};

