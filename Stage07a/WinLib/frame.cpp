#include "mywindows.h"
#include <iostream>
static Frame* globalFrame = NULL;  // 다른 파일에서는 사용할 수 없다.
// 전역함수로는 윈도 메시지 처리 함수가 있다.
LRESULT CALLBACK WndProc(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONUP:
	//case WM_KEYDOWN:
	//case WM_KEYUP:
	//case WM_CHAR:

	//case WM_MOUSEMOVE:
	{
		// processMessage
		globalFrame->processMessage(MyMessage(Msg, wParam, lParam)); // 파라메터 수정은 해야함
	}
	break;
	case WM_CREATE:
		break;
	case WM_SIZE:
	{
		std::string t;
		RECT rect;
		GetClientRect(Hw, &rect);
		t = std::to_string(rect.right - rect.left) + " X " + std::to_string(rect.bottom - rect.top);
		SetWindowTextA(Hw, t.c_str());
		std::cout << t << std::endl;
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Hw, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		// MainWindow  객체의 paint 를 호출한다.
		if (globalFrame && globalFrame->ready_)
			globalFrame->repaint();
		EndPaint(Hw, &ps);
	}
	break;
	default: return DefWindowProc(Hw, Msg, wParam, lParam);
	}
	return 0;
}

Frame::Frame(std::wstring title, int width, int height) {
	hInst_ = GetModuleHandle(NULL);
	FreeConsole(); // No console
	// Register win class
	WNDCLASSEX Wc;

	Wc.cbSize = sizeof(WNDCLASSEX);
	Wc.style = CS_HREDRAW | CS_VREDRAW;
	Wc.lpfnWndProc = WndProc;
	Wc.cbClsExtra = 0;
	Wc.cbWndExtra = 0;
	Wc.hInstance = hInst_;
	Wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wc.lpszMenuName = NULL;
	Wc.lpszClassName = L"MyWin";
	Wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&Wc);

	hWnd_ = CreateWindowExW( NULL /*WS_EX_TOPMOST */, L"MyWIn", (WCHAR*)title.c_str(),
		WS_OVERLAPPED |
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // 종료 최소화 최대화 아이콘
		WS_THICKFRAME,  // resize가 가능하게
		0, 0, width, height, // x, y, width, height
		NULL, NULL, hInst_, NULL);  // Parent, Menu, instance handle, lpParam
	if (!hWnd_) throw 0;

	hdc_ = GetDC(hWnd_);
	globalFrame = this;

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_); 
	SetFocus(hWnd_);
}

void Frame::run() {
	initialize(); // drawframe의 initialize
	HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));

	MSG msg;
	ready_ = true; // 여기 들어오기 전에는 모두 완결되었다고 보자.
	InvalidateRect(hWnd_, NULL, true); // PAINT 메시지가 하나 만들어지게 한다.

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))  // 없어도 무방.
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void Frame::repaint() {
	if (toolbar_)
		toolbar_->repaint();
	//OutputDebugStringA("Frame::repaint Called\n");
}
 
bool Frame::processMessage(MyMessage e) {
	Debug("Frame::processMessage Called\n");
	int result;
	
	/*int n = toolbar_->findbutton(e.x_, e.y_);
	if (n != -1) {
		mode = n;
	}*/
	
	btn = toolbar_->find(e.x_, e.y_);
	if (!toolbar_) return false;  // 툴바가 없다면 필요 없다.
	if (toolbar_->isToolBarEvent(e)) {
		// 툴바 이벤트라면 여기서 처리하고 응용에서 하지 않도록 true반환.
		toolbar_->processMessage(e);
		return true;
	}

	// 툴바 이벤트는 아니지만 이전에 마우스로 버튼을 눌렀으므로 응용에서 무시하도록 함.
	if (!toolbar_->isToolBarEvent(e) && toolbar_->pressed) {
		// 버튼등을 누른 후 다시 up 을 캔버스에서 한 경우 등.
			toolbar_->pressed = nullptr;
			return true;
	}
	

	return false;
}

void Frame::addToolBar(ToolBar* t) {
	toolbar_ = t;
	t->setParent(this);
}

void Frame::buttonCallBack(Button* b) {
	// override 를 기대함.
	//OutputDebugStringA("Callback at frame");
}

void Frame::initialize() {
	// 응용이 아니므로 기본 메뉴나 툴바는 없는 걸로 한다.
}

// =========== 전역 함수 ==============
HDC getMyDC() {
	return globalFrame->hdc_;
}
