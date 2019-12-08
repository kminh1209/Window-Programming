#include "group.h"
Group::Group(HDC hdc, int l, int t, int r, int b)
	: Shapestuff(hdc, l, t, r, b)
{
	OutputDebugStringW(L"�׷� ������\n");
}

void Group::add(Shapestuff *r) {
	Slist.push_back(r);
}

void Group::set_again(int l, int t, int r, int b) {
	left_ = l;
	top_ = t;
	right_ = r;
	bottom_ = b; // ó�� �����ɶ��� �ʿ亸�� ū ������ ������ �Ǿ����Ƿ� �����ϴ� ��ǥ�� ��ǥ�� �缳�����ش�.
	list<Shapestuff*>::iterator i;
	for (i = Slist.begin(); i != Slist.end(); i++)
	{
		(*i)->move(-l, -t); // �׷� ���� �������� ��ǥ�� �������� ��� �̵��Ҷ� �����Ϲɷ� ����η� �ٲ��ش�.
	}
}

void Group::repaint() {
	list<Shapestuff*>::iterator i;
	OutputDebugStringW(L"�׷� ������Ʈ\n");
	//Rectangle(hdc_, left_, top_, right_, bottom_);
	for (i = Slist.begin(); i != Slist.end(); i++) {
		(*i)->move(left_, top_); // �׸��� �׸��� �� ������� �����̹Ƿ� �׸������� �����η� �ٲ��ش�.
		(*i)->repaint();
		(*i)->move(-left_, -top_); // ���� �����η� ����� �����̹Ƿ� �ٽ� ����η� �����ش�.
	}
	OutputDebugStringW(L"�׷� ������Ʈ ����\n");
}