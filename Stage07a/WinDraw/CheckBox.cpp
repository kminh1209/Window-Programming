#include "CheckBox.h"
CheckBox::CheckBox(std::string title, int width, int height)
	: Button(title, width, height) {

}
void CheckBox::click_action() { 
	// Ŭ���� �ɶ����� state�� 0, 1�� �ݺ��ؼ� �ٲٰ� �Ѵ�. 
	state = i%2;
	i++;
}

void CheckBox::repaint() {
	HDC hdc = ::getMyDC();
	::Rectangle(hdc, x_, y_, x_ + width_, y_ + height_);
	title1_ = "��" + title_;
	title2_ = "��" + title_;
	if (state == 0) { 
		// üũ�� ���� �ʾ�����
		::TextOutA(hdc, x_ + 3, y_ + 3, title1_.c_str(), strlen(title1_.c_str()));
	}
	else if (state == 1){ 
		// üũ�� �Ǿ�����
		::TextOutA(hdc, x_ + 3, y_ + 3, title2_.c_str(), strlen(title2_.c_str()));
	}
}

int CheckBox::isChecked() { 
	// üũ ���¸� �˾ƺ��� �Լ�
	return state;
}