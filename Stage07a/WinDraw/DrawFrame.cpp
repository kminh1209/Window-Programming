#include "DrawFrame.h"
void DrawFrame::initialize() {
	// �ʱ�ȭ, ��ư �����, ���� ����...
	ToolBar* t = new ToolBar();
	btnSelectRect = new TextButton("�簢��", 100, 30);
	btnSelectEllipse = new TextButton("Ÿ��", 100, 30);
	btnSelectLine = new TextButton("����", 100, 30);
	informationCheck = new CheckBox("������������", 120, 30);
	searchCheck = new CheckBox("�˻����⵿��", 120, 30);
	CheckCheck = new TextButton("����Ȯ��", 100, 30);
	t->addButton(btnSelectRect); // ��ư�� �߰��Ѵ�.
	t->addButton(btnSelectEllipse);
	t->addButton(btnSelectLine);
	t->addButton(informationCheck);
	t->addButton(searchCheck);
	t->addButton(CheckCheck);
	this->addToolBar(t);
}

void DrawFrame::repaint() {
	// 
	Frame::repaint(); // ����/�޴� ���� �׸���.

	Rectangle(hdc_, 500, 500, 600, 600);  // ȣ��Ǵ��� Ȯ�� �������� �ӽ÷�.
	// �׸����� �׸����� ���⼭ �׷��ش�.
	for (i = shape_.begin(); i != shape_.end(); i++) {
		(*i)->repaint();
	}
}

bool DrawFrame::processMessage(MyMessage e) {
	if (!Frame::processMessage(e)) {
		//Debug("���뿡�� ó������.");
		if (e.isMouseEvent()) {


			if (e.event_type_ == WM_RBUTTONDOWN) {
				// ��Ŭ�� �巡�׸� �Ǻ��ϴ� �κ�
				startx = e.x_;
				starty = e.y_;
			}
			else if (e.event_type_ == WM_RBUTTONUP) {
				arrange(startx, starty, e.x_, e.y_); // �񱳸� ���� ũ������� ����.
				Group* group = new Group(hdc_, left, top, right, bottom);
				bool iscontain = false;
				int l = -1, t, r, b;
				for (i = shape_.begin(); i != shape_.end(); i++) {

					if ((*i)->iscontain(left, top, right, bottom)) {
						group->add(*i); // �������ο� ������ �ǹǷ� �׷쿡 ������ �߰����ش�.
						if (l == -1)
						{
							// ó������ ���� ���� ���� ������ ó�� ���� ���ο� ���Ե� ������ �߰��Ͽ������� ����ǵ��� �Ѵ�.
							l = (*i)->getLeft();
							t = (*i)->getTop();
							r = (*i)->getRight();
							b = (*i)->getBottom();
						}
						l = min(l, (*i)->getLeft()); // �����ϴ� �ּҿ���.
						t = min(t, (*i)->getTop());
						r = max(r, (*i)->getRight());
						b = max(b, (*i)->getBottom());
						iscontain = true;
					}

				}

				if (iscontain) {
					group->set_again(l, t, r, b);
					shape_.push_back(group);
					list <Shapestuff*>::iterator it;
					for (it = group->Slist.begin(); it != group->Slist.end(); it++) {
						OutputDebugStringW(L"���� ����");
						shape_.remove(*it);
					}
					repaint();
				}
			}



			if (e.event_type_ == WM_LBUTTONDOWN) {
				startx = e.x_;
				starty = e.y_;
			}
			else if (e.event_type_ == WM_LBUTTONUP) {

				// ���� ���θ� Ŭ���ߴ��� �˾ƺ��� �ݺ���
				for (list <Shapestuff*>::reverse_iterator it = shape_.rbegin(); it != shape_.rend(); it++) {

					if ((*it)->belongs(startx, starty)) {
						// ���� ���� ��Ŭ�� ���� ��
						(*it)->move(e.x_ - startx, e.y_ - starty);
						InvalidateRect(hWnd_, NULL, true); // �̵�
						j = 1; // ���� ���� ��Ŭ�� ���� ���� ���¸� ��Ÿ��.
						break;
					}
				}
				arrange(0, 0, 0, 0); // ���� �ʱ�ȭ
				if (j == 0) {
					//���� ���� ��Ŭ�� ���� �ʾ��� ��

					// ���� �ϴܿ��� �����ؼ� ���� ������� ������, ���� ��ܿ��� ���� �ϴ����� ������ � �� �Ȱ��� �Էµ� �� �ֵ��� �ϴ� �Լ�
					if (mode == 0) {
						shape_.push_back(new CRectangle(hdc_, startx, starty, e.x_, e.y_));
					}
					else if (mode == 1) {
						shape_.push_back(new CCircle(hdc_, startx, starty, e.x_, e.y_));
					}
					else if (mode == 2) {
						shape_.push_back(new CLine(hdc_, startx, starty, e.x_, e.y_));
					}
				}
				j = 0; // j �ʱ�ȭ
				InvalidateRect(hWnd_, NULL, true);
				repaint();
			}
		}
	}
	return true;
}
void DrawFrame::buttonCallBack(Button* b) {
	int n = 0;
	int h = 0;
	list <Button*>::iterator it;
	for (it = toolbar_->buttons_.begin(); n < toolbar_->num_buttons_; it++) {
		// ���ư�� �������� �˻��ϰ� �̸� mode�� ����
		if ((*it) == b) {
			if (n < 3) { // n�� 0(�簢�� ��ư), 1(Ÿ�� ��ư), 2(���� ��ư)�� �� ��带 �ٲ۴�.
				mode = n;
			}
			else if (n == 3) {
				informationState = (*it)->isChecked(); // ������������ ��ư�� ���������� �� ���¸� ��ȯ�ϵ��� �Ѵ�.
			}
			else if (n == 4) {
				searchState = (*it)->isChecked(); // �˻����⵿�� ��ư�� ���������� �� ���¸� ��ȯ�ϵ��� �Ѵ�.
			}
			else if (n == 5) {
				// ����Ȯ�� ��ư�� ��������
				h = 1;
			}

		}
		n++;
	}
	if (h == 1) {
		if (informationState == 0) { // �������� üũ�ڽ�
			OutputDebugStringW(L"������������\n");
		}
		else {
			OutputDebugStringW(L"������������\n");
		}
		if (searchState == 0) { // �˻����� üũ�ڽ�
			OutputDebugStringW(L"�˻��������\n");
		}
		else {
			OutputDebugStringW(L"�˻����⵿��\n");
		}
	}
	Debug("Callback at Application - ");
	Debug(b->getTitleStr());
	repaint();
}

void DrawFrame::arrange(int sx, int sy, int x, int y) {
	//�񱳸� ���� ũ��� ����
	if (sx <= x && sy <= y) {
		left = sx;
		top = sy;
		right = x;
		bottom = y;
	}
	else if (sx >= x && sy <= y) {
		left = x;
		top = sy;
		right = sx;
		bottom = y;
	}
	else if (sx <= x && sy >= y) {
		left = sx;
		top = y;
		right = x;
		bottom = sy;
	}
	else if (sx >= x && sy >= y) {
		left = x;
		top = y;
		right = sx;
		bottom = sy;
	}
}

DrawFrame::DrawFrame(std::wstring title, int width, int height) : Frame(title, width, height) {
	num_ = 0;

}
DrawFrame::DrawFrame(std::wstring title) : DrawFrame(title, 1000, 800)
{
	//
}
