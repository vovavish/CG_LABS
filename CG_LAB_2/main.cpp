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
		600,
		600,
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

// y = sin(x)
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
//
//		a = sx / 2;
//		b = sy / 2;
//
//		SelectObject(hdc, hpen1);
//		MoveToEx(hdc, 0, b, NULL);
//		LineTo(hdc, sx, b);
//		MoveToEx(hdc, a, 0, NULL);
//		LineTo(hdc, a, sy);
//		MoveToEx(hdc, 0, b, NULL);
//		SelectObject(hdc, hpen2);
//
//		h = M_PI / a;
//		
//		for (x = -M_PI, x_scr = 0; x < M_PI; x += h)
//		{
//			x_scr = (x + M_PI) * a / M_PI;
//			y_scr = b - b * sin(x);
//			LineTo(hdc, x_scr, y_scr);
//		}
//		
//		EndPaint(hWnd, &ps);
//
//		break;
//
//	case WM_DESTROY:
//		DeleteObject(hpen1);
//		DeleteObject(hpen2);
//		PostQuitMessage(0);
//		break;
//
//	default: return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}

// y = x * x
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
//		h = 3. / a;
//		for (x = -3, x_scr = 0; x < 3; x += h)
//		{
//			x_scr = (x + 3) * a / 3;
//			y_scr = b - b * x*x; 
//
//			if (x == -3)
//			{
//				MoveToEx(hdc, x_scr, y_scr, NULL);
//			}
//
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

// rotation 1
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//	static HPEN hpen1, hpen2;
//	int a, b, n, x_scr, y_scr, z_scr;
//	double x, y, z;
//	double x_min, x_max, y_min, y_max, Kx, Ky;
//	static int sx, sy;
//
//	switch (message)
//	{
//	case WM_CREATE:
//		hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
//		hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
//		break;
//
//	case WM_SIZE:
//		sx = LOWORD(lParam);
//		sy = HIWORD(lParam);
//		break;
//
//	case WM_PAINT:
//		x_min = -100;
//		x_max = 100;
//		y_min = -100;
//		y_max = 100;
//
//		a = sx / 2;
//		b = sy / 2;
//
//		Kx = (sx - 220) / (x_max - x_min);
//		Ky = (sy - 220) / (y_max - y_min);
//
//		hdc = BeginPaint(hWnd, &ps);
//
//		SelectObject(hdc, hpen1);
//		MoveToEx(hdc, 0, b, NULL);
//		LineTo(hdc, sx, b);
//		MoveToEx(hdc, 20, sy - 20, NULL);
//		LineTo(hdc, sx - 20, 20);
//
//		MoveToEx(hdc, 0, b, NULL);
//		LineTo(hdc, sx, b);
//		MoveToEx(hdc, a, 0, NULL);
//		LineTo(hdc, a, sy);
//		MoveToEx(hdc, 0, b, NULL);
//		SelectObject(hdc, hpen1);
//
//		n = y_max - y_min;
//
//		for (y = y_min; y < y_max; y += 5)
//		{
//			hpen2 = CreatePen(PS_SOLID, 2, RGB(255,
//					255 - 255. / n * (y + y_min),
//					255 - 255. / n * (y + y_min)));
//
//			SelectObject(hdc, hpen2);
//
//			z = b - 100 * sin(M_PI / 50 * sqrt(x_min * x_min + y * y));
//			MoveToEx(hdc, x_min * Kx + a + y, (z + y), NULL);
//
//			for (x = x_min; x < x_max; x += 5)
//			{
//				z = b - 100 * sin(M_PI / 50 * sqrt(x * x + y * y));
//				LineTo(hdc, x * Kx + a + y, z + y);
//			}
//		}
//		
//		EndPaint(hWnd, &ps);
//		break;
//		case WM_DESTROY:
//			DeleteObject(hpen1);
//			DeleteObject(hpen2);
//			PostQuitMessage(0);
//			break;
//		
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//
//	return 0;
//}

// var 2: y = x * x + 5 * x + 3
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//	static int sx, sy;
//	static HPEN hpen1, hpen2;
//	int a, b, x_scr, y_scr, scaleX;
//	double x, h;
//
//	switch (message) {
//	case WM_CREATE:
//		hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
//		hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
//		break;
//
//	case WM_SIZE:
//		sx = LOWORD(lParam);
//		sy = HIWORD(lParam);
//		break;
//
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//
//		a = sx / 2;
//		b = sy / 2;
//
//		SelectObject(hdc, hpen1);
//		MoveToEx(hdc, 0, b, NULL);
//		LineTo(hdc, sx, b);
//		MoveToEx(hdc, a, 0, NULL);
//		LineTo(hdc, a, sy);
//		MoveToEx(hdc, 0, b, NULL);
//		SelectObject(hdc, hpen2);
//
//		h = M_PI / a;
//		for (x = -10; x < 10; x += h)
//		{
//			x_scr = (x + 10.0f) * a / 10.0f;
//			y_scr = b - b * (5 * x * x + 2 * x + 3) / 10;
//
//			if (x == -10)
//			{
//				MoveToEx(hdc, x_scr, y_scr, NULL);
//			}
//
//			LineTo(hdc, x_scr, y_scr);
//		}
//
//		EndPaint(hWnd, &ps);
//		break;
//
//	case WM_DESTROY:
//		DeleteObject(hpen1);
//		DeleteObject(hpen2);
//		PostQuitMessage(0);
//		break;
//
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}

// rotation 2
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static HPEN hpen1, hpen2;
	int a, b, n, x_scr, y_scr, z_scr;
	double x, y, z;
	double x_min, x_max, y_min, y_max, Kx, Ky;
	static int sx, sy;

	switch (message)
	{
	case WM_CREATE:
		hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		break;

	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;

	case WM_PAINT:
		x_min = -100;
		x_max = 100;
		y_min = -100;
		y_max = 100;

		a = sx / 2;
		b = sy / 2;

		Kx = (sx - 220) / (x_max - x_min);
		Ky = (sy - 220) / (y_max - y_min);

		hdc = BeginPaint(hWnd, &ps);

		SelectObject(hdc, hpen1);
		MoveToEx(hdc, 0, b, NULL);
		LineTo(hdc, sx, b);
		MoveToEx(hdc, 20, sy - 20, NULL);
		LineTo(hdc, sx - 20, 20);

		MoveToEx(hdc, 0, b, NULL);
		LineTo(hdc, sx, b);
		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a, sy);
		MoveToEx(hdc, 0, b, NULL);
		SelectObject(hdc, hpen1);

		n = y_max - y_min;

		for (y = y_min; y < y_max; y += 5)
		{
			hpen2 = CreatePen(PS_SOLID, 2, RGB(255,
					255 - 255. / n * (y + y_min),
					255 - 255. / n * (y + y_min)));

			SelectObject(hdc, hpen2);
			
			double x_temp = sqrt(x_min * x_min + y * y);
			//z = b - 0.1 * (x_temp * x_temp);
			z = b - 0.01 * (5 * x_temp * x_temp + 2 * x_temp + 3);

			MoveToEx(hdc, x_min * Kx + a + y, (z + y), NULL);

			for (x = x_min; x < x_max; x += 5)
			{
				double x_temp2 = sqrt(x * x + y * y);
				//z = (b - 0.1 * (x_temp2 * x_temp2)) * 0.9;
				z = (b - 0.01 * (5 * x_temp2 * x_temp2 + 2 * x_temp2 + 3)) * 0.9;
				LineTo(hdc, x * Kx + a + y, (z + y));
			}
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