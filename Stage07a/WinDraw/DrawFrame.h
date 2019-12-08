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
	DrawFrame(std::wstring); // �⺻ ������
	DrawFrame(std::wstring, int, int);
	virtual void initialize();
	virtual bool processMessage(MyMessage e);
	virtual void repaint();
	virtual void buttonCallBack(Button* b);
	void arrange(int sx, int sy, int x, int y);
	

// ��ư��.
	Button* btnSelectRect = nullptr;
	Button* btnSelectEllipse = nullptr;
	Button* btnSelectLine = nullptr;
	Button* informationCheck = nullptr;
	Button* searchCheck = nullptr;
	Button* CheckCheck = nullptr;

// stage 9 ���� �߰��� ��
	list <Shapestuff*> shape_;
	list <Shapestuff*> Rshape_;
	list <Shapestuff*>::iterator i;

//�ӽú���
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
	int j = 0; // 0: ���� ���� ��Ŭ�� ���� ���� ���� 1: ���� ���� ��Ŭ�� �� ����

	int informationState = 0; // �������� ���� ���� ����
	int searchState = 0; // �˻����� ���� ���� ����

	int leftMost = 0;
	int topMost = 0;
	int rightMost = 0;
	int bottomMost = 0;

	
};


