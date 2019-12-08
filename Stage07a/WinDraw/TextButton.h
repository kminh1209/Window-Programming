#pragma once
#include "Button.h"
#include "frame.h"
class TextButton :
	public Button
{
public:
	TextButton(std::string title, int width, int height);
	virtual void repaint();
	virtual int isChecked();
};

