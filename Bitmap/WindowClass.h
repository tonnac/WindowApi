#pragma once
#include "Std.h"
#include "Input.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	Window();
public:
	void					SetInstance(HINSTANCE);
	RECT					getClient();
public:
	bool					SetWindow();
	bool					Run();
private:
	virtual bool			GameInit();
	virtual bool			GameRun();
	virtual bool			GameRelease();
public:
	virtual LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
private:
	void					CenterWindow();
private:
	int						m_iCmdShow;
	MSG						m_mMsg;
	WNDCLASSEX				m_wcWD;
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;
protected:
	RECT					m_rtClient;
	RECT					m_rtWindow;
};