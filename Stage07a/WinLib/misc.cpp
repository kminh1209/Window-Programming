#include "misc.h"
#include <stdio.h>

MyMessage::MyMessage(UINT msg, WPARAM wp, LPARAM lp) {
	event_type_ = msg;
	x_ = LOWORD(lp);
	y_ = HIWORD(lp);
	this->wp_ = wp;
}

bool MyMessage::isCtrlPressed() {
	return (wp_ & MK_CONTROL); 
}

bool MyMessage::isShiftPressed() {
	return (wp_ & MK_SHIFT);
}

bool MyMessage::isMouseEvent() {
	return event_type_ == WM_LBUTTONDOWN 
		|| event_type_ == WM_LBUTTONUP 
		|| event_type_ == WM_LBUTTONDBLCLK
		|| event_type_ == WM_RBUTTONDOWN 
		|| event_type_ == WM_RBUTTONUP 
		|| event_type_ == WM_LBUTTONDBLCLK;
}

// =========================

void Debug(const char* s) {
	static int seq = 1;
	char buf[128];
	sprintf_s(buf, "%d. %s\n", seq++, s);
	OutputDebugStringA(buf);
}

void Debug(int n) {
	char buf[128];
	sprintf_s(buf, " %d\n", n);
	Debug(buf);
}