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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
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
		for (i = 0; i <= n; i++) {
			for (j = 0; j <= 3; j++) {
				ptl[j].x = 500 + (pt[j].x * cos(alpha * i) - pt[j].y * sin(alpha * i)) + i * 10;
				ptl[j].y = 300 + (pt[j].x * sin(alpha * i) + pt[j].y * cos(alpha * i));
			}
			hBrush = CreateSolidBrush(RGB(255, 255 - 255 / n * i, 255 - 255 / n * i));
			BeginPath(hdc);
			Polygon(hdc, ptl, 4);
			CloseFigure(hdc);
			EndPath(hdc);
			SelectObject(hdc, hBrush);
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


//LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
//	WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	POINT pt[3] = { {-63,100},{13,100},{-25, 0} };
//	POINT pt_2[3] = { {-63,30},{13,30},{-25, 130} };
//
//	POINT ptl[3];
//	const int WIDTH = 400;
//	const int HEIGHT = 300;
//	int n = 3, i, j;
//	double alpha = M_PI / n;
//	int sx, sy;
//	static HBRUSH hBrush, hBrush2, hBrush3;
//	sx = LOWORD(lParam);
//	sy = HIWORD(lParam);
//	switch (message) {
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//
//		for (i = 0; i <= n; i++)
//		{
//			for (j = 0; j <= 2; j++)
//			{
//				ptl[j].x = 500 + (pt[j].x * cos(alpha * i) - pt[j].y * sin(alpha * i)) + i * 10;
//				ptl[j].y = 300 + (pt[j].x * sin(alpha * i) + pt[j].y * cos(alpha * i));
//			}
//			hBrush3 = CreateSolidBrush(RGB(255 - 255 / n * i, 0, 0));
//			BeginPath(hdc);
//			Polygon(hdc, ptl, 3);
//			CloseFigure(hdc);
//			EndPath(hdc);
//			SelectObject(hdc, hBrush);
//			SetPolyFillMode(hdc, WINDING);
//			FillPath(hdc);
//		
//		}
//
//		for (i = 0; i <= n; i++) {
//			for (j = 0; j <= 2; j++) {
//				ptl[j].x = 500 + (pt_2[j].x * cos(alpha * i) - pt_2[j].y * sin(alpha * i)) + i * 10;
//				ptl[j].y = 300 + (pt_2[j].x * sin(alpha * i) + pt_2[j].y * cos(alpha * i));
//			}
//
//			hBrush = CreateSolidBrush(RGB(255, 255 - 255 / n * i, 255 - 255 / n * i));
//			BeginPath(hdc);
//			Polygon(hdc, ptl, 3);
//			CloseFigure(hdc);
//			EndPath(hdc);
//			SelectObject(hdc, hBrush3);
//			SetPolyFillMode(hdc, WINDING);
//			FillPath(hdc);
//
//		}
//
//		EndPaint(hWnd, &ps);
//
//		break;
//	case WM_DESTROY: PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}