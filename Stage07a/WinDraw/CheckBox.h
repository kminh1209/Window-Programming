#pragma once
#include "Button.h"
#include "frame.h"
class CheckBox :
	public Button
{
public:
	CheckBox(std::string title, int width, int height);
	virtual void click_action();
	virtual void repaint();
	virtual int isChecked();
private:
	int state = 0; // 체크했는지 상태를 나타내는 변수
	int i = 1; 
};

