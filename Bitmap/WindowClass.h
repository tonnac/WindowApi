#pragma once
#include "Std.h"
#include "Input.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Window
{
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	Window();
public:
	bool				setWindow(HINSTANCE);
	bool				Run();
private:
	virtual bool		GameInit();
	virtual bool		GameRun();
	virtual bool		GameRelease();
	LRESULT CALLBACK	MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
private:
	void				CenterWindow();
private:
	HWND				m_hWnd;
	RECT				m_rtClient;
	RECT				m_rtWindow;
};