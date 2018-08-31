#include "stdafx.h"
#include "Magic.h"
#include "CommonClass.h"

LRESULT CALLBACK winProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

HWND Magic::init(HINSTANCE hInstance,const char * lpName, const char * lpClass, int width, int height)
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

	if (!RegisterClass(&wcex))
	{
		return 0;
	}

	hwnd = CreateWindow(
		lpClass,
		lpName,
		WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return hwnd;
}

Magic::~Magic()
{
	if (IsWindow(hwnd)) CloseWindow(hwnd);
}

