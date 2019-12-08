#include "Button.h"
#include "Frame.h"
#include "ToolBar.h"
Button::Button(std::string title, int width, int height)
:title_(title), x_(0), y_(0), width_(width), height_(height){
	//title1_ = "□" + title_;
	//title2_ = "▣" + title_;
}

bool Button::belongs(int x, int y) {
	//버튼을 클릭했는지 판별
	return x_ < x && x < x_ + width_
		&& y_ < y && y < y_ + height_;
}
bool Button::processMessage(MyMessage e) {
	if (e.event_type_ == WM_LBUTTONDOWN) {
		parent_->pressed = this;
		return true;
	} 
	else if (e.event_type_ == WM_LBUTTONUP && parent_->pressed == this) {
		click_action(); // 체크박스를 클릭했을때 
		Frame* f = getRootFrame();
		if (f) {
			f->buttonCallBack(this);
			parent_->pressed = nullptr;
			return true;
		}
		parent_->pressed = nullptr;
	} else
		return false;
}

void Button::click_action() {
	//empty
	// CheckBox의 함수에서 처리함.
}

void Button::repaint() {
	/*HDC hdc = ::getMyDC();
	::Rectangle(hdc, x_, y_, x_ + width_, y_ + height_);
	::TextOutA(hdc, x_ + 3, y_ + 3, title_.c_str(), strlen(title_.c_str()));*/
	//각각의 가상함수에서 처리하게끔 한다.
}

void Button::setParent(ToolBar* t) {
	parent_ = t;
}

Frame* Button::getRootFrame() {
	return parent_ == nullptr ? nullptr : parent_->getParent();
}

const char* Button::getTitleStr() {
	return title_.c_str();
}
int Button::getX() {
	return x_;
}

void Button::setX(int x) {
	x_ = x;
}

int Button::getY() {
	return y_;
}

void Button::setY(int y) {
	y_ = y;
}

int Button::getWidth() {
	return width_;
}

void Button::setWidth(int w) {
	width_ = w;
}

int Button::getHeight() {
	return height_;
}

void Button::setHeight(int h) {
	height_ = h;
}