#pragma once
#include <frame.h>
#include <list>
#include "Shape.h"
#include "Shapestuff.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CLine.h"
#include "TextButton.h"
#include "CheckBox.h"
#include "group.h"
using namespace std;
class DrawFrame :
	public Frame
{
public:
	DrawFrame(std::wstring); // 기본 생성자
	DrawFrame(std::wstring, int, int);
	virtual void initialize();
	virtual bool processMessage(MyMessage e);
	virtual void repaint();
	virtual void buttonCallBack(Button* b);
	void arrange(int sx, int sy, int x, int y);
	

// 버튼들.
	Button* btnSelectRect = nullptr;
	Button* btnSelectEllipse = nullptr;
	Button* btnSelectLine = nullptr;
	Button* informationCheck = nullptr;
	Button* searchCheck = nullptr;
	Button* CheckCheck = nullptr;

// stage 9 새로 추가한 것
	list <Shapestuff*> shape_;
	list <Shapestuff*> Rshape_;
	list <Shapestuff*>::iterator i;

//임시변수
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
	int j = 0; // 0: 도형 안을 우클릭 하지 않은 상태 1: 도형 안을 우클릭 한 상태

	int informationState = 0; // 정보공개 동의 여부 변수
	int searchState = 0; // 검색노출 동의 여부 변수

	int leftMost = 0;
	int topMost = 0;
	int rightMost = 0;
	int bottomMost = 0;

	
};


