#pragma once
#include <Windows.h>
#include <list>
#include "misc.h"
using namespace std;
class Button;
class Frame;
class ToolBar
{
public:
	ToolBar();
	//HDC hdc_;
	void addButton(Button* b);
	bool processMessage(MyMessage e);
	void repaint();
	bool belongs(int x, int y);
	bool isToolBarEvent(MyMessage e);
	Button * find(int, int);
	void setParent(Frame* f);
	Frame* getParent();  // Frame의 포인터 구하기
	//Button* buttons_[100];
	list<Button*> buttons_;
	list<Button*>:: iterator i;
	int num_buttons_ = 0;
	int x_, y_, width_, height_;
	Frame* parent_;
	Button* pressed = nullptr;  // 메뉴 버튼의 누르고 뗌을 추적
	//int findbutton(int x, int y);


};

