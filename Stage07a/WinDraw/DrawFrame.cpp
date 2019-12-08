#include "DrawFrame.h"
void DrawFrame::initialize() {
	// 초기화, 버튼 만들기, 툴바 생성...
	ToolBar* t = new ToolBar();
	btnSelectRect = new TextButton("사각형", 100, 30);
	btnSelectEllipse = new TextButton("타원", 100, 30);
	btnSelectLine = new TextButton("선분", 100, 30);
	informationCheck = new CheckBox("정보공개동의", 120, 30);
	searchCheck = new CheckBox("검색노출동의", 120, 30);
	CheckCheck = new TextButton("내용확인", 100, 30);
	t->addButton(btnSelectRect); // 버튼을 추가한다.
	t->addButton(btnSelectEllipse);
	t->addButton(btnSelectLine);
	t->addButton(informationCheck);
	t->addButton(searchCheck);
	t->addButton(CheckCheck);
	this->addToolBar(t);
}

void DrawFrame::repaint() {
	// 
	Frame::repaint(); // 툴바/메뉴 등을 그린다.

	Rectangle(hdc_, 500, 500, 600, 600);  // 호출되는지 확인 차원에서 임시로.
	// 그림판의 그림들을 여기서 그려준다.
	for (i = shape_.begin(); i != shape_.end(); i++) {
		(*i)->repaint();
	}
}

bool DrawFrame::processMessage(MyMessage e) {
	if (!Frame::processMessage(e)) {
		//Debug("응용에서 처리하자.");
		if (e.isMouseEvent()) {


			if (e.event_type_ == WM_RBUTTONDOWN) {
				// 우클릭 드래그를 판별하는 부분
				startx = e.x_;
				starty = e.y_;
			}
			else if (e.event_type_ == WM_RBUTTONUP) {
				arrange(startx, starty, e.x_, e.y_); // 비교를 위해 크기순으로 정렬.
				Group* group = new Group(hdc_, left, top, right, bottom);
				bool iscontain = false;
				int l = -1, t, r, b;
				for (i = shape_.begin(); i != shape_.end(); i++) {

					if ((*i)->iscontain(left, top, right, bottom)) {
						group->add(*i); // 영역내부에 포함이 되므로 그룹에 도형을 추가해준다.
						if (l == -1)
						{
							// 처음에는 비교할 값이 없기 때문에 처음 영역 내부에 포함된 도형을 발견하였을때만 실행되도록 한다.
							l = (*i)->getLeft();
							t = (*i)->getTop();
							r = (*i)->getRight();
							b = (*i)->getBottom();
						}
						l = min(l, (*i)->getLeft()); // 내접하는 최소영역.
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
						OutputDebugStringW(L"도형 삭제");
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

				// 도형 내부를 클릭했는지 알아보는 반복문
				for (list <Shapestuff*>::reverse_iterator it = shape_.rbegin(); it != shape_.rend(); it++) {

					if ((*it)->belongs(startx, starty)) {
						// 도형 안을 좌클릭 했을 시
						(*it)->move(e.x_ - startx, e.y_ - starty);
						InvalidateRect(hWnd_, NULL, true); // 이동
						j = 1; // 도형 안을 좌클릭 했을 때의 상태를 나타냄.
						break;
					}
				}
				arrange(0, 0, 0, 0); // 변수 초기화
				if (j == 0) {
					//도형 안을 좌클릭 하지 않았을 때

					// 우측 하단에서 시작해서 좌측 상단으로 끝날때, 우측 상단에서 좌측 하단으로 끝날때 등도 다 똑같이 입력될 수 있도록 하는 함수
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
				j = 0; // j 초기화
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
		// 어떤버튼을 눌렀는지 검사하고 이를 mode에 저장
		if ((*it) == b) {
			if (n < 3) { // n이 0(사각형 버튼), 1(타원 버튼), 2(선분 버튼)일 때 모드를 바꾼다.
				mode = n;
			}
			else if (n == 3) {
				informationState = (*it)->isChecked(); // 정보공개동의 버튼을 누를때마다 그 상태를 반환하도록 한다.
			}
			else if (n == 4) {
				searchState = (*it)->isChecked(); // 검색노출동의 버튼을 누를때마다 그 상태를 반환하도록 한다.
			}
			else if (n == 5) {
				// 내용확인 버튼을 눌렀을때
				h = 1;
			}

		}
		n++;
	}
	if (h == 1) {
		if (informationState == 0) { // 정보공개 체크박스
			OutputDebugStringW(L"정보공개비동의\n");
		}
		else {
			OutputDebugStringW(L"정보공개동의\n");
		}
		if (searchState == 0) { // 검색노출 체크박스
			OutputDebugStringW(L"검색노출비동의\n");
		}
		else {
			OutputDebugStringW(L"검색노출동의\n");
		}
	}
	Debug("Callback at Application - ");
	Debug(b->getTitleStr());
	repaint();
}

void DrawFrame::arrange(int sx, int sy, int x, int y) {
	//비교를 위한 크기순 정렬
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
