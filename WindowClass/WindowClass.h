#pragma once
#include "Std.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	bool setWindow(HINSTANCE);
	bool Run();
private:
	HWND m_hWnd;
};