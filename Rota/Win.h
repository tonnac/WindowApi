#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

extern HINSTANCE				g_hInstance;
extern HWND						g_hWnd;
extern HDC						g_hScreenDC;
extern HDC						g_hOffScreenDC;

class Window
{
public:
	Window(HINSTANCE, LONG, LONG);
public:
	bool				SetWindow();
	bool				Run();
protected:
	virtual bool		GameInit();
	virtual bool		GameFrame();
	virtual bool		GameRender();
	virtual bool		GameRelease();
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
private:
	void				CenterWindow();
protected:
	MSG					m_mMsg;
	RECT				m_rtClient;
	RECT				m_rtWindow;
	HINSTANCE			m_hInstance;
	WNDCLASSEX			m_wdWindowClass;
	HWND				m_hWnd;
};