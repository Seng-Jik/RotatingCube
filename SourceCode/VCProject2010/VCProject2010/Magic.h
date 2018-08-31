#pragma once
class Magic
{
private:
	HWND hwnd;
public:
	HWND init(HINSTANCE hInstance, const char * lpName, const char * lpClass,int width,int height);
	HWND hwnd() { return hwnd; }
	~Magic();
};

