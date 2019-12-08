#pragma once
#include <string>
#include "misc.h"
class ToolBar;
class Frame;
class Button
{
public:
	Button(std::string title, int width, int height);
	bool belongs(int x, int y); // 버튼을 클릭했는지 판별하는 함수
	bool processMessage(MyMessage e); // 버튼을 클릭했을 시에 여기서 처리한다.
	virtual void repaint(); // 다형성을 위해서 TextButton과 CheckBox에서 각각 그리도록 한다.
	int getX(); int getY(); int getHeight(); int getWidth();
	void setX(int); void setY(int); void setHeight(int); void setWidth(int);
	const char* getTitleStr();
	//ToolBar* getParent();
	void setParent(ToolBar*);
	virtual void click_action(); //체크박스의 상태를 바꿔줄 함수
	virtual int isChecked() = 0;//
protected:
	std::string title_;
	std::string title1_; // □ + title_ 을 저장
	std::string title2_; // ▣ + title_ 을 저장
	int x_, y_;  // Position
	int width_, height_;
	ToolBar* parent_ = nullptr;
public:
	Frame* getRootFrame();
};

