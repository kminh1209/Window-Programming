#include "TextButton.h"
TextButton::TextButton(std::string title, int width, int height)
	: Button(title, width, height){

}
void TextButton::repaint() {
	HDC hdc = ::getMyDC();
	::Rectangle(hdc, x_, y_, x_ + width_, y_ + height_);
	::TextOutA(hdc, x_ + 3, y_ + 3, title_.c_str(), strlen(title_.c_str()));
}
int TextButton::isChecked() {
	return 1;
}