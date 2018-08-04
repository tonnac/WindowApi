#include "WindowClass.h"

HWND g_hWnd = nullptr;
Window * g_pWindow = nullptr;		//WndProc()
HINSTANCE g_hInstance = nullptr;

RECT g_rtClient;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT ret;
	if (ret = g_pWindow->MsgProc(hwnd, msg, wparam, lparam))
	{
		return ret;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

Window::Window()
{
	g_pWindow = this;
}
void Window::SetInstance(HINSTANCE hinst)
{
	m_hInstance = hinst;
}
bool Window::SetWindow()
{
	ZeroMemory(&m_mMsg, sizeof(MSG));
	ZeroMemory(&m_wcWD, sizeof(WNDCLASSEX));
	m_wcWD.cbSize = sizeof(WNDCLASSEX);
	m_wcWD.style = CS_HREDRAW | CS_VREDRAW;
	m_wcWD.hInstance = g_hInstance = m_hInstance;
	m_wcWD.lpfnWndProc = WndProc;
//	m_wcWD.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_wcWD.lpszMenuName = L"Window";
	m_wcWD.lpszClassName = L"ClassName";

	if (!RegisterClassEx(&m_wcWD))
	{
		return false;
	}
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		m_wcWD.lpszClassName,
		m_wcWD.lpszMenuName,
		WS_OVERLAPPEDWINDOW,
		0, 0,
		1024, 768,
		nullptr,
		nullptr,
		m_wcWD.hInstance,
		nullptr);
	assert(m_hWnd != nullptr);
	g_hWnd = m_hWnd;
	GetClientRect(m_hWnd, &m_rtClient);


	g_rtClient = m_rtClient;

	GetWindowRect(m_hWnd, &m_rtWindow);
	CenterWindow();
	return true;
}
bool Window::Run()
{
	if (!GameInit())
	{
		return false;
	}
	if (ShowWindow(m_hWnd, SW_SHOW))
	{
		return false;
	}

	while (m_mMsg.message != WM_QUIT)
	{
		if (PeekMessage(&m_mMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_mMsg);
			DispatchMessage(&m_mMsg);
		}
		else
		{
			GameRun();			
		}
	}
	return GameRelease();
}

bool Window::GameInit()
{
	return true;
}
bool Window::GameRun()
{
	return true;
}
bool Window::GameRelease()
{
	return true;
}

LRESULT CALLBACK Window::MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return 0;
}


void Window::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = ((iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2);
	int y = ((iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2);
	MoveWindow(m_hWnd, x, y, m_rtWindow.right - m_rtWindow.left, m_rtWindow.bottom - m_rtWindow.top, true);
}