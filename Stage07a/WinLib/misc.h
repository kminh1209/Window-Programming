#pragma once
#include <Windows.h>

class MyMessage {
	// 굳이 클래스일 필요 없다.
public:
	MyMessage(UINT msg, WPARAM wp, LPARAM lp);
	bool isCtrlPressed();
	bool isShiftPressed();
	bool isMouseEvent();
	UINT event_type_;
	WPARAM wp_;
	int x_, y_;
};

struct Point {
	Point(int x, int y) :x(x), y(y) {}
	int x, y;
};

void Debug(int);
void Debug(const char *);