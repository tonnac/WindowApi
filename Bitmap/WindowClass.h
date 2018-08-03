#pragma once
#include "Std.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	Window(HINSTANCE = 0);
public:
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Redner();
	virtual bool			Release();
private:
	void					CenterWindow();
private:
	MSG						m_mMsg;
	WNDCLASSEX				m_wcWD;
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;
	RECT					m_rtClient;
	RECT					m_rtWindow;
};