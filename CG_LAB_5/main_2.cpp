//#define _USE_MATH_DEFINES
//#include <math.h>
//#include <windows.h>
//#include <tchar.h>
//#include <fstream>
//
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//TCHAR WinName[] = _T("MainFrame");
//
//static int sx, sy;
//const int SCALE = 1000;
//const int MARK = 4;
//
//void DcInLp(POINT& point)
//{
//	point.x = point.x * SCALE / sx;
//	point.y = SCALE - point.y * SCALE / sy;
//}
//
//void transform(HDC& hdc)
//{
//	SetMapMode(hdc, MM_ANISOTROPIC);
//	SetWindowExtEx(hdc, SCALE, -SCALE, NULL);
//	SetViewportExtEx(hdc, sx, sy, NULL);
//	SetViewportOrgEx(hdc, 0, sy, NULL);
//}
//
//int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd, int mode)
//{
//	HWND hWnd;
//	MSG msg;
//	WNDCLASS wc;
//
//	wc.hInstance = This;
//	wc.lpszClassName = WinName;
//	wc.lpfnWndProc = WndProc;
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.lpszMenuName = NULL;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//
//	if (!RegisterClass(&wc))
//	{
//		return 0;
//	}
//
//	hWnd = CreateWindow(WinName,
//		_T("Каркас Windows-приложения"),
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		HWND_DESKTOP,
//		NULL,
//		This,
//		NULL);
//	ShowWindow(hWnd, mode);
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	return 0;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//	static HPEN hDash, hBezier;
//	static HBRUSH hRect, hSel;
//	static POINT pt[20];
//	static POINT point;
//	RECT rt;
//	static int count, index;
//	static bool capture;
//	int i;
//	std::ifstream in;
//	std::ofstream out;
//
//	switch (message)
//	{
//	case WM_CREATE:
//		in.open("data.txt");
//
//		if (in.fail()) {
//			MessageBox(hWnd, _T("Файл data.txt не найден"), _T("Открытие файла"), MB_OK | MB_ICONEXCLAMATION);
//			PostQuitMessage(0);
//			return 1;
//		}
//
//		for (count = 0; in >> pt[count].x; count++)
//		{
//			in >> pt[count].y;
//		}
//
//		in.close();
//
//		hDash = CreatePen(PS_DASH, 1, 0);
//		hBezier = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
//		hRect = CreateSolidBrush(RGB(128, 0, 128));
//		hSel = CreateSolidBrush(RGB(255, 0, 0));
//		break;
//
//	case WM_SIZE:
//		sx = LOWORD(lParam);
//		sy = HIWORD(lParam);
//		break;
//
//	case WM_LBUTTONDOWN:
//		point.x = LOWORD(lParam);
//		point.y = HIWORD(lParam);
//
//		DcInLp(point);
//
//		for (i = 0; i <= count; i++)
//		{
//			SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
//
//			if (PtInRect(&rt, point))
//			{
//				index = i;
//				capture = true;
//				hdc = GetDC(hWnd);
//				transform(hdc);
//				FillRect(hdc, &rt, hSel);
//				ReleaseDC(hWnd, hdc);
//				SetCapture(hWnd);
//				return 0;
//			}
//		}
//		break;
//
//	case WM_LBUTTONUP:
//		if (capture)
//		{
//			ReleaseCapture();
//			capture = false;
//		}
//		break;
//
//	case WM_MOUSEMOVE:
//		if (capture)
//		{
//			point.x = LOWORD(lParam);
//			point.y = HIWORD(lParam);
//			DcInLp(point);
//			pt[index] = point;
//			InvalidateRect(hWnd, NULL, true);
//		}
//		break;
//
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		transform(hdc);
//		SelectObject(hdc, hDash);
//		Polyline(hdc, pt, count);
//		SelectObject(hdc, hBezier);
//		PolyBezier(hdc, pt, count);
//
//		for (i = 0; i < count; i++)
//		{
//			SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
//			FillRect(hdc, &rt, hRect);
//		}
//		break;
//
//	case WM_DESTROY:
//		DeleteObject(hDash);
//		DeleteObject(hBezier);
//		DeleteObject(hRect);
//		DeleteObject(hSel);
//		out.open("data1.txt");
//		for (i = 0; i < count; i++)
//		{
//			out << pt[i].x << '\t' << pt[i].y << '\n';
//		}
//
//		out.close();
//		break;
//
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}
