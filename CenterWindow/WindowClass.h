#pragma once
#include "Std.h"
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	bool			setWindow(HINSTANCE);
	bool			Run();
private:
	void			CenterWindow();
private:
	HWND			m_hWnd;
	RECT			m_rtClient;
	RECT			m_rtWindow;
};