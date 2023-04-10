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

void DrawBSplines(HDC hdc, POINT* points, int n) {
	for (int i = 1; i < n - 1; i++) {
		POINT pt;
		POINT ans[4];
		POINT bezi[N];
		int cnt = 0;
		ans[3].x = (-points[i - 1].x + 3 * (points[i].x - points[i + 1].x) + points[i + 2].x) / 6.;
		ans[3].y = (-points[i - 1].y + 3 * (points[i].y - points[i + 1].y) + points[i + 2].y) / 6.;
		ans[2].x = (points[i - 1].x - 2 * points[i].x + points[i + 1].x) / 2.;
		ans[2].y = (points[i - 1].y - 2 * points[i].y + points[i + 1].y) / 2.;
		ans[1].x = (points[i + 1].x - points[i - 1].x) / 2.;
		ans[1].y = (points[i + 1].y - points[i - 1].y) / 2.;
		ans[0].x = (points[i - 1].x + 4 * points[i].x + points[i + 1].x) / 6.;
		ans[0].y = (points[i - 1].y + 4 * points[i].y + points[i + 1].y) / 6.;
		for (int j = 0; j < N; j++) {
			float t = (float)j / (float)N;
			pt.x = ((ans[3].x * t + ans[2].x) * t + ans[1].x) * t + ans[0].x;
			pt.y = ((ans[3].y * t + ans[2].y) * t + ans[1].y) * t + ans[0].y;
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
		if (in.fail()) {
			MessageBox(hWnd, _T("Файл data.txt не найден"), _T("Открытие файла"), MB_OK | MB_ICONEXCLAMATION);
			PostQuitMessage(0);
			return 1;
		}
		for (count = 0; in >> pt[count].x; count++) in >> pt[count].y;
		in.close();
		hDash = CreatePen(PS_DASH, 1, 0);
		hBezier = CreatePen(PS_SOLID, 4, RGB(128, 128, 255));
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
		for (i = 0; i <= count; i++) {
			SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
			if (PtInRect(&rt, point)) {
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
		if (capture) {
			ReleaseCapture();
			capture = false;
		}
		break;

	case WM_MOUSEMOVE:
		if (capture) {
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
