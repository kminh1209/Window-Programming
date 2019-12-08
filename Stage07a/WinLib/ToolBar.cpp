#include "ToolBar.h"
#include "Button.h"
ToolBar::ToolBar(){
	// Empty
}
void ToolBar::addButton(Button* b) {
	//this->buttons_[num_buttons_] = b; //������ Ŭ������ ����
	buttons_.push_back(b);
	b->setParent(this);
	// ���� ��ư�� ��ġ�� ��������.
	
	int w = 0; height_ = 0;
	int n = 0;
	for (i = buttons_.begin(); n < num_buttons_; i++) {
		w += (*i)->getWidth();
		height_ = max(height_, (*i)->getHeight());
		n++;
	}
	b->setX(w);
	
	num_buttons_++; //��ư�� �߰��� ������ �÷���
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