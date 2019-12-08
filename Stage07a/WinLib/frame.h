#pragma once
#include <Windows.h>
#include "mywindows.h"
#include <string>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
class ToolBar;
class Button;
class Frame {
public:
	Frame(std::wstring, int, int);
	virtual bool processMessage(MyMessage e);
	virtual void run();
	virtual void initialize();
	virtual void repaint();
	virtual void addToolBar(ToolBar* t);
	virtual void buttonCallBack(Button* b);

	Button* btn = nullptr;
	ToolBar* toolbar_ = nullptr;
	HINSTANCE hInst_;
	HWND hWnd_;
	HDC hdc_;
	bool ready_ = false;
	int startx = 0, starty = 0;
	int mode = 0;
	int num_ = 0;

};

HDC getMyDC();