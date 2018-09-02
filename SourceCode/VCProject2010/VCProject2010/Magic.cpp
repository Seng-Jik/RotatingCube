#include "stdafx.h"
#include "Magic.h"
#include "CommonClass.h"

LRESULT CALLBACK winProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void Magic::UpdateWindow(HWND& h,HINSTANCE hInstance,const char * lpName, const char * lpClass, int width, int height)
{
	WNDCLASS  wcex;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = winProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = lpClass;

	RECT r;
	GetWindowRect(h, &r);

	if (!RegisterClass(&wcex))
	{
		abort();
	}

	hwnd = CreateWindow(
		lpClass,
		lpName,
		WS_SYSMENU,
		r.left,
		r.top,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	h = hwnd;
}

Magic::~Magic()
{
	if (IsWindow(hwnd)) CloseWindow(hwnd);
}

