#pragma once
#include <string>
#include "misc.h"
class ToolBar;
class Frame;
class Button
{
public:
	Button(std::string title, int width, int height);
	bool belongs(int x, int y); // ��ư�� Ŭ���ߴ��� �Ǻ��ϴ� �Լ�
	bool processMessage(MyMessage e); // ��ư�� Ŭ������ �ÿ� ���⼭ ó���Ѵ�.
	virtual void repaint(); // �������� ���ؼ� TextButton�� CheckBox���� ���� �׸����� �Ѵ�.
	int getX(); int getY(); int getHeight(); int getWidth();
	void setX(int); void setY(int); void setHeight(int); void setWidth(int);
	const char* getTitleStr();
	//ToolBar* getParent();
	void setParent(ToolBar*);
	virtual void click_action(); //üũ�ڽ��� ���¸� �ٲ��� �Լ�
	virtual int isChecked() = 0;//
protected:
	std::string title_;
	std::string title1_; // �� + title_ �� ����
	std::string title2_; // �� + title_ �� ����
	int x_, y_;  // Position
	int width_, height_;
	ToolBar* parent_ = nullptr;
public:
	Frame* getRootFrame();
};

