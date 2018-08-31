#include "stdafx.h"
#include "Magic.h"
#include "CommonClass.h"

HWND Magic::init(HINSTANCE hInstance,const char * lpName, const char * lpClass, int width, int height)
{
	WNDCLASS  wcex;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = NULL;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "HJ";

	if (!RegisterClass(&wcex))
	{
		return 0;
	}

	this->hwnd = CreateWindow(
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

	ShowWindow(this->hwnd, SW_SHOW);
	UpdateWindow(this->hwnd);

	return this->hwnd;
}

Magic::~Magic()
{
	if (IsWindow(this->hwnd)) CloseWindow(this->hwnd);
}

