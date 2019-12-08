#include "mywindows.h"
#include <iostream>
static Frame* globalFrame = NULL;  // �ٸ� ���Ͽ����� ����� �� ����.
// �����Լ��δ� ���� �޽��� ó�� �Լ��� �ִ�.
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
		globalFrame->processMessage(MyMessage(Msg, wParam, lParam)); // �Ķ���� ������ �ؾ���
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
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		// MainWindow  ��ü�� paint �� ȣ���Ѵ�.
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
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // ���� �ּ�ȭ �ִ�ȭ ������
		WS_THICKFRAME,  // resize�� �����ϰ�
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
	initialize(); // drawframe�� initialize
	HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));

	MSG msg;
	ready_ = true; // ���� ������ ������ ��� �ϰ�Ǿ��ٰ� ����.
	InvalidateRect(hWnd_, NULL, true); // PAINT �޽����� �ϳ� ��������� �Ѵ�.

	// �⺻ �޽��� �����Դϴ�:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))  // ��� ����.
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
	if (!toolbar_) return false;  // ���ٰ� ���ٸ� �ʿ� ����.
	if (toolbar_->isToolBarEvent(e)) {
		// ���� �̺�Ʈ��� ���⼭ ó���ϰ� ���뿡�� ���� �ʵ��� true��ȯ.
		toolbar_->processMessage(e);
		return true;
	}

	// ���� �̺�Ʈ�� �ƴ����� ������ ���콺�� ��ư�� �������Ƿ� ���뿡�� �����ϵ��� ��.
	if (!toolbar_->isToolBarEvent(e) && toolbar_->pressed) {
		// ��ư���� ���� �� �ٽ� up �� ĵ�������� �� ��� ��.
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
	// override �� �����.
	//OutputDebugStringA("Callback at frame");
}

void Frame::initialize() {
	// ������ �ƴϹǷ� �⺻ �޴��� ���ٴ� ���� �ɷ� �Ѵ�.
}

// =========== ���� �Լ� ==============
HDC getMyDC() {
	return globalFrame->hdc_;
}
