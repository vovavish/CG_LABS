#include <windows.h>
#include <tchar.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd,	int mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(WinName,
		_T("Каркас Windows-приложения"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500,
		500,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);
	ShowWindow(hWnd, mode);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK print_red_star(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	POINT pt[5] = { {0, 100},{-59, -81},{95, 31}, {-95, 31}, {59, -81} };

	const int WIDTH = 400;
	const int HEIGHT = 300;
	static int sx, sy, i, k;
	static HBRUSH hBrush;
	double x, h;

	switch (message) {
	case WM_CREATE:
		i = MessageBox(hWnd, _T("Будем рисовать красную звезду?"), _T("Политический вопрос"), MB_YESNO | MB_ICONQUESTION);
		k = (i == IDYES) ? 1 : 0;
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		hdc = BeginPaint(hWnd, &ps);
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, WIDTH, -HEIGHT, NULL);
		SetViewportExtEx(hdc, sx, sy, NULL);
		SetViewportOrgEx(hdc, sx / 2, sy / 2, NULL);

		BeginPath(hdc);
		Polyline(hdc, pt, 5);
		CloseFigure(hdc);
		EndPath(hdc);
		SelectObject(hdc, hBrush);
		SetPolyFillMode(hdc, WINDING);
		FillPath(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK print_6star(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	//int sizeOfStar = 100;
	//POINT pt[6] = { {-sizeOfStar, sizeOfStar / (2.5 / 1.5)}, {0, sizeOfStar * 1.2}, {sizeOfStar, sizeOfStar / (2.5 / 1.5)},
	//				 {sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {0, -sizeOfStar * 1.2}, {-sizeOfStar, -sizeOfStar / (2.5 / 1.5)} };
	//POINT pt2[3] = { {-sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {0, sizeOfStar * 1.2} };

	int sizeOfStar = 100;
	POINT pt[3] = { {-sizeOfStar,sizeOfStar / (2.5 / 1.5)}, {sizeOfStar, sizeOfStar / (2.5 / 1.5)}, {0, -sizeOfStar * 1.2},};
	POINT pt2[3] = { {-sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {0, sizeOfStar * 1.2} };

	//POINT pt3[12] = { {-sizeOfStar,sizeOfStar / (2.5 / 1.5)}, {-sizeOfStar * 2 / 3, sizeOfStar / (2.5 / 1.5)}, {0, sizeOfStar * 1.2},
	//				  {sizeOfStar * 2 / 3, sizeOfStar / (2.5 / 1.5)}, {sizeOfStar, sizeOfStar / (2.5 / 1.5)}, {sizeOfStar * 2 / 3, 0},
	//				  {sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {0, -sizeOfStar * 1.2},
	//				  {-sizeOfStar * 2 / 3, -sizeOfStar / (2.5 / 1.5)}, {-sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {-sizeOfStar * 2 / 3, 0} };

	const int WIDTH = 400;
	const int HEIGHT = 300;
	static int sx, sy, i, k;
	static HBRUSH hBrush, hBrush2;
	switch (message) {
	case WM_CREATE:
		i = MessageBox(hWnd, _T("Будем рисовать шестиконечную звезду?"), _T("Политический вопрос"), MB_YESNO | MB_ICONQUESTION);
		k = (i == IDYES) ? 1 : 0;
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		hdc = BeginPaint(hWnd, &ps);
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, WIDTH, -HEIGHT, NULL);
		SetViewportExtEx(hdc, sx, sy, NULL);
		SetViewportOrgEx(hdc, sx / 2, sy / 2, NULL);

		BeginPath(hdc);
		Polyline(hdc, pt, 3);
		CloseFigure(hdc);
		EndPath(hdc);
		SelectObject(hdc, hBrush);
		SetPolyFillMode(hdc, WINDING);
		FillPath(hdc);

		BeginPath(hdc);
		Polyline(hdc, pt2, 3);
		CloseFigure(hdc);
		EndPath(hdc);
		SelectObject(hdc, hBrush);

		SetPolyFillMode(hdc, WINDING);
		FillPath(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return print_red_star(hWnd, message, wParam, lParam);
	//return print_6star(hWnd, message, wParam, lParam);

	return 0;
}