#include "CheckBox.h"
CheckBox::CheckBox(std::string title, int width, int height)
	: Button(title, width, height) {

}
void CheckBox::click_action() { 
	// 클릭이 될때마다 state가 0, 1을 반복해서 바꾸게 한다. 
	state = i%2;
	i++;
}

void CheckBox::repaint() {
	HDC hdc = ::getMyDC();
	::Rectangle(hdc, x_, y_, x_ + width_, y_ + height_);
	title1_ = "□" + title_;
	title2_ = "▣" + title_;
	if (state == 0) { 
		// 체크가 되지 않았을때
		::TextOutA(hdc, x_ + 3, y_ + 3, title1_.c_str(), strlen(title1_.c_str()));
	}
	else if (state == 1){ 
		// 체크가 되었을때
		::TextOutA(hdc, x_ + 3, y_ + 3, title2_.c_str(), strlen(title2_.c_str()));
	}
}

int CheckBox::isChecked() { 
	// 체크 상태를 알아보는 함수
	return state;
}