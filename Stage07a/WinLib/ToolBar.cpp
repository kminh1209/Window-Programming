#include "ToolBar.h"
#include "Button.h"
ToolBar::ToolBar(){
	// Empty
}
void ToolBar::addButton(Button* b) {
	//this->buttons_[num_buttons_] = b; //각각의 클래스에 저장
	buttons_.push_back(b);
	b->setParent(this);
	// 이제 버튼의 위치를 조정하자.
	
	int w = 0; height_ = 0;
	int n = 0;
	for (i = buttons_.begin(); n < num_buttons_; i++) {
		w += (*i)->getWidth();
		height_ = max(height_, (*i)->getHeight());
		n++;
	}
	b->setX(w);
	
	num_buttons_++; //버튼을 추가할 때마다 늘려줌
}

bool ToolBar::processMessage(MyMessage e) {
	if (e.isMouseEvent()) {
		Button* b = find(e.x_, e.y_);
		if (b) {
			b->processMessage(e);
			return true;
		}
		return false;
	}
	
	return false;
}
Button * ToolBar::find(int x, int y) {
	int n = 0;
	for (i = buttons_.begin(); n < num_buttons_; i++) {
		if ((*i)->belongs(x, y))
			return (*i);
		n++;
	}
	return nullptr;
}



/*int ToolBar::findbutton(int x, int y) {
	for (int i = 0; i < num_buttons_; i++) {
		if (buttons_[i]->belongs(x, y))
			return i;
	}
	return -1;
}*/

void ToolBar::setParent(Frame* f) {
	parent_ = f;
}

Frame* ToolBar::getParent() {
	return parent_;
}

bool ToolBar::belongs(int x, int y) {
	return (y < height_);
}
void ToolBar::repaint() {
	int n = 0;
	for (i = buttons_.begin(); n < num_buttons_; i++) {
		(*i)->repaint();
		n++;
	}
}
bool ToolBar::isToolBarEvent(MyMessage e) {
	if (e.isMouseEvent() && find(e.x_, e.y_))
		return true;
	return false;
}