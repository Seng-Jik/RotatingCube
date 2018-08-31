#pragma once
class Magic
{
private:
	HWND hwnd;
public:
	HWND UpdateWindow(HWND&,HINSTANCE hInstance, const char * lpName, const char * lpClass,int width,int height);
	~Magic();
};

