#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include <fstream>
#define N 30

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

static int sx, sy;
const int SCALE = 1000;
const int MARK = 4;

//
//void DrawBSplines(HDC hdc, POINT points[], int count)
//{
//	int xA, xB, xC, xD, yA, yB, yC, yD, N = 20;
//	double a0, a1, a2, a3, b0, b1, b2, b3, t, X, Y;
//	static POINT point;
//	for (int i = 1; i < count - 1; i++)
//	{
//		xA = points[i - 1].x;
//		yA = points[i - 1].y;
//		xB = points[i].x;
//		yB = points[i].y;
//		xC = points[i + 1].x;
//		yC = points[i + 1].y;
//		xD = points[i + 2].x;
//		yD = points[i + 2].y;
//
//		a3 = (-xA + 3 * (xB - xC) + xD) / 6.0; b3 = (-yA + 3 * (yB - yC) + yD) / 6.0;
//		a2 = (xA - 2 * xB + xC) / 2.0; b2 = (yA - 2 * yB + yC) / 2.0;
//		a1 = (xC - xA) / 2.0; b1 = (yC - yA) / 2.0;
//		a0 = (xA + 4 * xB + xC) / 6.0; b0 = (yA + 4 * yB + yC) / 6.0;
//
//		bool isFirst = true;
//
//		for (int j = 0; j <= N; j++)
//		{
//			float t = (float)j / (float)N;
//			X = ((a3 * t + a2) * t + a1) * t + a0;
//			Y = ((b3 * t + b2) * t + b1) * t + b0;
//			if (isFirst)
//			{
//				MoveToEx(hdc, X, Y, NULL);
//				isFirst = false;
//			}
//			else
//			{
//				LineTo(hdc, X, Y);
//			}
//		}
//	}
//}
//

void DrawBSplines(HDC hdc, POINT* points, int n) {
	for (int i = 1; i < n - 1; i++) {
		POINT pt;
		POINT a[4];
		POINT bezi[N];
		int cnt = 0;

		a[3].x = (-points[i - 1].x + 3 * (points[i].x - points[i + 1].x) + points[i + 2].x) / 6.0f;
		a[3].y = (-points[i - 1].y + 3 * (points[i].y - points[i + 1].y) + points[i + 2].y) / 6.0f;
		a[2].x = (points[i - 1].x - 2 * points[i].x + points[i + 1].x) / 2.0f;
		a[2].y = (points[i - 1].y - 2 * points[i].y + points[i + 1].y) / 2.0f;
		a[1].x = (points[i + 1].x - points[i - 1].x) / 2.0f;
		a[1].y = (points[i + 1].y - points[i - 1].y) / 2.0f;
		a[0].x = (points[i - 1].x + 4 * points[i].x + points[i + 1].x) / 6.0f;
		a[0].y = (points[i - 1].y + 4 * points[i].y + points[i + 1].y) / 6.0f;
		
		for (int j = 0; j < N; j++)
		{
			float t = (float)j / (float)N;
			pt.x = ((a[3].x * t + a[2].x) * t + a[1].x) * t + a[0].x;
			pt.y = ((a[3].y * t + a[2].y) * t + a[1].y) * t + a[0].y;
			bezi[cnt++] = pt;
		}

		PolyBezierTo(hdc, bezi, N);
	}
}

void DcInLp(POINT& point) {
	point.x = point.x * SCALE / sx;
	point.y = SCALE - point.y * SCALE / sy;
}

void transform(HDC& hdc) {
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, SCALE, -SCALE, NULL);
	SetViewportExtEx(hdc, sx, sy, NULL);
	SetViewportOrgEx(hdc, 0, sy, NULL);
}

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
	static HPEN hDash, hBezier;
	static HBRUSH hRect, hSel;
	static POINT pt[20];
	static POINT point;
	RECT rt;
	static int count, index;
	static bool capture;
	int i;
	std::ifstream in;
	std::ofstream out;
	int degree;
	POINT* p;
	switch (message)
	{
	case WM_CREATE:
		in.open("data.txt");

		if (in.fail())
		{
			MessageBox(hWnd, _T("Файл data.txt не найден"), _T("Открытие файла"), MB_OK | MB_ICONEXCLAMATION);
			PostQuitMessage(0);
			return 1;
		}

		for (count = 0; in >> pt[count].x; count++)
		{
			in >> pt[count].y;
		}
		
		in.close();
		hDash = CreatePen(PS_DASH, 1, 0);
		hBezier = CreatePen(PS_SOLID, 4, RGB(50, 127, 200));
		hRect = CreateSolidBrush(RGB(128, 0, 128));
		hSel = CreateSolidBrush(RGB(255, 0, 0));
		break;

	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;

	case WM_LBUTTONDOWN:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		DcInLp(point);
		for (i = 0; i <= count; i++)
		{	
			SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
			
			if (PtInRect(&rt, point))
			{
				index = i;
				capture = true;
				hdc = GetDC(hWnd);
				transform(hdc);
				FillRect(hdc, &rt, hSel);
				ReleaseDC(hWnd, hdc);
				SetCapture(hWnd);
				return 0;
			}
		}
		break;

	case WM_LBUTTONUP:
		if (capture)
		{
			ReleaseCapture();
			capture = false;
		}
		break;

	case WM_MOUSEMOVE:
		if (capture)
		{
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			DcInLp(point);
			pt[index] = point;
			InvalidateRect(hWnd, NULL, true);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		transform(hdc);
		SelectObject(hdc, hDash);
		Polyline(hdc, pt, count);
		MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
		SelectObject(hdc, hBezier);
		DrawBSplines(hdc, pt, count);

		for (i = 0; i < count; i++)
		{
			SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
			FillRect(hdc, &rt, (i == index) ? hSel : hRect);
			Rectangle(hdc, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
		}

		EndPaint(hWnd, &ps);

		break;

	case WM_DESTROY:
		DeleteObject(hDash);
		DeleteObject(hBezier);
		DeleteObject(hRect);
		DeleteObject(hSel);

		out.open("data1.txt");

		for (i = 0; i < count; i++)
		{
			out << pt[i].x << '\t' << pt[i].y << '\n';
		}

		out.close();
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
