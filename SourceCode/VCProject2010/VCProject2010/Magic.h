#pragma once
class Magic
{
public:
	HWND hwnd;
	HWND init(HINSTANCE hInstance, const char * lpName, const char * lpClass,int width,int height);
	~Magic();
};

