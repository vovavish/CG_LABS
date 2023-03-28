#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
#include <tchar.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd,
	int mode)
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

LRESULT CALLBACK rotation_red_star(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	POINT pt[4] = { {-100,100},{-100,-100},{100,-100},{100,100} };
	POINT ptl[4];
	const int WIDTH = 400;
	const int HEIGHT = 300;
	int n = 8, i, j;
	double alpha = M_PI / n;
	int sx, sy;
	static HBRUSH hBrush;
	sx = LOWORD(lParam);
	sy = HIWORD(lParam);
	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (i = 0; i <= n; i++)
		{
			hBrush = CreateSolidBrush(RGB(255, 255 - 255 / n * i, 255 - 255 / n * i));
			SelectObject(hdc, hBrush);
			for (j = 0; j <= 3; j++)
			{
				ptl[j].x = 500 + (pt[j].x * cos(alpha * i) - pt[j].y * sin(alpha * i)) + i * 10;
				ptl[j].y = 300 + (pt[j].x * sin(alpha * i) + pt[j].y * cos(alpha * i));
			}
			BeginPath(hdc);
			Polygon(hdc, ptl, 4);
			CloseFigure(hdc);
			EndPath(hdc);
			SetPolyFillMode(hdc, WINDING);
			FillPath(hdc);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


LRESULT CALLBACK rotation_6star(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	int sizeOfStar = 100;
	POINT pt1[3] = { {-sizeOfStar,sizeOfStar / (2.5 / 1.5)}, {sizeOfStar, sizeOfStar / (2.5 / 1.5)}, {0, -sizeOfStar * 1.2} };
	POINT pt2[3] = { {-sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {sizeOfStar, -sizeOfStar / (2.5 / 1.5)}, {0, sizeOfStar * 1.2} };

	POINT ptl[3];

	const int WIDTH = 400;
	const int HEIGHT = 300;
	int n = 4, i, j;
	double alpha = M_PI / n;
	int sx, sy;
	static HBRUSH hBrush1, hBrush2;
	
	sx = LOWORD(lParam);
	sy = HIWORD(lParam);
	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (i = 0; i <= n; i++)
		{
			for (j = 0; j < 3; j++)
			{
				ptl[j].x = 500 + (pt1[j].x * cos(alpha * i) - pt1[j].y * sin(alpha * i)) + i * 10;
				ptl[j].y = 200 + (pt1[j].x * sin(alpha * i) + pt1[j].y * cos(alpha * i));
			}

			BeginPath(hdc);

			SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));
			Polygon(hdc, ptl, 3);

			hBrush1 = CreateSolidBrush(RGB(255 - 255 / n * i, 255 - 255 / n * i, 255));
			SelectObject(hdc, hBrush1);

			CloseFigure(hdc);
			EndPath(hdc);
			SetPolyFillMode(hdc, WINDING);
			FillPath(hdc);

			hBrush2 = CreateSolidBrush(RGB(255 - 255 / n * i, 255 - 255 / n * i, 255));
			SelectObject(hdc, hBrush2);

			for (j = 0; j < 3; j++)
			{
				ptl[j].x = 500 + (pt2[j].x * cos(alpha * i) - pt2[j].y * sin(alpha * i)) + i * 10;
				ptl[j].y = 200 + (pt2[j].x * sin(alpha * i) + pt2[j].y * cos(alpha * i));
			}

			BeginPath(hdc);

			SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));
			Polygon(hdc, ptl, 3);
			hBrush2 = CreateSolidBrush(RGB(255 - 255 / n * i, 255 - 255 / n * i, 255));
			SelectObject(hdc, hBrush2);
			CloseFigure(hdc);
			EndPath(hdc);
			SetPolyFillMode(hdc, WINDING);
			FillPath(hdc);
		
		}

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
	return rotation_red_star(hWnd, message, wParam, lParam);
	//return rotation_6star(hWnd, message, wParam, lParam);

	return 0;
}