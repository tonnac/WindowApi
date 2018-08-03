#pragma once
#include "Std.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	void					SetInstance(HINSTANCE);
public:
	bool					SetWindow();
	bool					Run();
private:
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Render();
	virtual bool			Release();
private:
	void					CenterWindow();
private:
	int						m_iCmd;
	MSG						m_mMsg;
	WNDCLASSEX				m_wcWD;
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;
	RECT					m_rtClient;
	RECT					m_rtWindow;
};