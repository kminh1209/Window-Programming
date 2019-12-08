#include "group.h"
Group::Group(HDC hdc, int l, int t, int r, int b)
	: Shapestuff(hdc, l, t, r, b)
{
	OutputDebugStringW(L"그룹 생성자\n");
}

void Group::add(Shapestuff *r) {
	Slist.push_back(r);
}

void Group::set_again(int l, int t, int r, int b) {
	left_ = l;
	top_ = t;
	right_ = r;
	bottom_ = b; // 처음 생성될때는 필요보다 큰 범위로 생성이 되었으므로 내접하는 좌표로 좌표를 재설정해준다.
	list<Shapestuff*>::iterator i;
	for (i = Slist.begin(); i != Slist.end(); i++)
	{
		(*i)->move(-l, -t); // 그룹 내부 도형들의 좌표가 절대경로일 경우 이동할때 불편하믈로 상대경로로 바꿔준다.
	}
}

void Group::repaint() {
	list<Shapestuff*>::iterator i;
	OutputDebugStringW(L"그룹 리페인트\n");
	//Rectangle(hdc_, left_, top_, right_, bottom_);
	for (i = Slist.begin(); i != Slist.end(); i++) {
		(*i)->move(left_, top_); // 그림을 그리기 전 상대경로인 상태이므로 그리기전에 절대경로로 바꿔준다.
		(*i)->repaint();
		(*i)->move(-left_, -top_); // 값이 절대경로로 변경된 상태이므로 다시 상대경로로 돌려준다.
	}
	OutputDebugStringW(L"그룹 리페인트 끄읕\n");
}