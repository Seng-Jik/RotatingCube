#pragma once
class Magic
{
private:
	HWND hwnd;
public:
	void UpdateWindow(HWND&,HINSTANCE hInstance, const char * lpName, const char * lpClass,int width,int height);
	~Magic();
};

