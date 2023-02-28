#define _USE_MATH_DEFINES 
#include <windows.h>
#include <tchar.h>
#include <math.h>


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
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(WinName, _T("Каркас Widows-приложения"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		400,
		400,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);
	ShowWindow(hWnd, mode);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} return 0;

}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//	static int sx, sy;
//	static HPEN hpen1, hpen2;
//	int a, b, x_scr, y_scr;
//	double x, h;
//
//	switch (message) {
//	case WM_CREATE:
//		hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
//		hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
//		break;
//	case WM_SIZE:
//		sx = LOWORD(lParam);
//		sy = HIWORD(lParam);
//		break;
//
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		a = sx / 2;
//		b = sy / 2;
//		SelectObject(hdc, hpen1);
//		MoveToEx(hdc, 0, b, NULL);
//		LineTo(hdc, sx, b);
//		MoveToEx(hdc, a, 0, NULL);
//		LineTo(hdc, a, sy);
//		MoveToEx(hdc, 0, b, NULL);
//		SelectObject(hdc, hpen2);
//		h = 3 * 3.14159265358979323846 / a;
//		for (x = -3.14159265358979323846, x_scr = 0; x < 3.14159265358979323846; x += h)
//		{
//			x_scr = (x + 6) * a / 3.14159265358979323846;
//			y_scr = b - b * sin(x);
//			LineTo(hdc, x_scr, y_scr);
//		}
//		EndPaint(hWnd, &ps);
//		break;
//	case WM_DESTROY:
//		DeleteObject(hpen1);
//		DeleteObject(hpen2);
//		PostQuitMessage(0);
//		break;
//	default: return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}

/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static int sx, sy;
	static HPEN hpen1, hpen2;
	int a, b, x_scr, y_scr;
	double x, h;

	switch (message) {
	case WM_CREATE:
		hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		a = sx / 2;
		b = sy / 2;
		SelectObject(hdc, hpen1);
		MoveToEx(hdc, 0, b, NULL);
		LineTo(hdc, sx, b);
		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a, sy);
		MoveToEx(hdc, 0, b, NULL);
		SelectObject(hdc, hpen2);
		h = 3 * 3.14159265358979323846 / a;
		for (x = -3.14159265358979323846, x_scr = 0; x < 3.14159265358979323846; x += h)
		{
			x_scr = (x + 3.14159265358979323846) * a / 3.14159265358979323846;
			y_scr = b - b * x*x;
			LineTo(hdc, x_scr, y_scr);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hpen1);
		DeleteObject(hpen2);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
*/


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static int sx, sy;
	static HPEN hpen1, hpen2;
	int a, b, x_scr, y_scr, scaleX;
	double x, h;

	switch (message) {
	case WM_CREATE:
		hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		break;

	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		a = sx / 2;
		b = sy / 2;

		SelectObject(hdc, hpen1);
		MoveToEx(hdc, 0, b, NULL);
		LineTo(hdc, sx, b);
		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a, sy);
		MoveToEx(hdc, 0, b, NULL);
		SelectObject(hdc, hpen2);

		h = 3 * M_PI / a;
		scaleX = 3;
		for (x = -scaleX; x < scaleX; x += h)
		{
			x_scr = (x + 3.0f) * a / 3;

			double temp = (5 * x * x + 2 * x - 1.2f) / 3.4f;
			y_scr = - b * temp;
			
			/*x_scr = (x + scaleX) * a / scaleX;
			y_scr = b - scaleX * (5 * x * x + 2 *x +3);*/

			x_scr = (x + scaleX) * a / scaleX;
			y_scr = b - scaleX/10*b * (5 * x * x + 2 * x+3) ;

			if (x == -3)
			{
				MoveToEx(hdc, x_scr, y_scr, NULL);
			}

			LineTo(hdc, x_scr, y_scr);
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(hpen1);
		DeleteObject(hpen2);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
