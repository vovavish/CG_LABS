#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd, int mode)
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

	if (!RegisterClass(&wc))
	{
		return 0;
	}

	hWnd = CreateWindow(
		WinName,
		_T("Каркас Windows-приложения"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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

void paint_circle(HDC hdc, int x1, int y1, int radius, HBRUSH hbrush)
{
	SelectObject(hdc, hbrush);
	Ellipse(hdc, x1 - radius, y1 - radius, x1 + radius, y1 + radius);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static int sx, sy;
	static HBRUSH hbrush_green, hbrush_black, hbrush_gray, hbrush_cyan, hbrush_yellow;
	static int radius;
	static int xmid, ymid;
	static int padding;

	switch (message)
	{
	case WM_CREATE:

		hbrush_green = CreateSolidBrush(RGB(0, 255, 0));
		hbrush_black = CreateSolidBrush(RGB(0, 0, 0));
		hbrush_gray = CreateSolidBrush(RGB(190, 190, 190));
		hbrush_cyan = CreateSolidBrush(RGB(0, 255, 255));
		hbrush_yellow = CreateSolidBrush(RGB(255, 255, 0));

	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);

		if (sx > sy)
		{
			radius = sy * 0.2f;
			padding = sy * 0.03f;
		}
		else
		{
			radius = sx * 0.2f;
			padding = sx * 0.03f;
		}

		xmid = sx / 2;
		ymid = sy / 2;

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (sx >= 20)
		{
			for (int x = 0; x < sx; x += (sx / 10))
			{
				MoveToEx(hdc, x, 0, NULL);
				LineTo(hdc, x, sy);
			}
		}

		if (sy >= 20)
		{
			for (int y = 0; y < sy; y += (sy / 10))
			{
				MoveToEx(hdc, 0, y, NULL);
				LineTo(hdc, sx, y);
			}
		}

		paint_circle(hdc, xmid, ymid - radius + padding, radius, hbrush_green);
		paint_circle(hdc, xmid - radius + padding, ymid, radius, hbrush_cyan);
		paint_circle(hdc, xmid, ymid + radius - padding, radius, hbrush_black);
		paint_circle(hdc, xmid + radius - padding, ymid, radius, hbrush_gray);
		paint_circle(hdc, xmid, ymid, radius, hbrush_yellow);

		EndPaint(hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
