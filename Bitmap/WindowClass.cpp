#include "WindowClass.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

Window::Window(HINSTANCE hinst) : m_hInstance(hinst)
{}

bool Window::Init()
{
	ZeroMemory(&m_mMsg, sizeof(MSG));
	ZeroMemory(&m_wcWD, sizeof(WNDCLASSEX));
	m_wcWD.cbSize = sizeof(WNDCLASSEX);
	m_wcWD.style = CS_HREDRAW | CS_VREDRAW;
	m_wcWD.hInstance = m_hInstance;
	m_wcWD.lpfnWndProc = WndProc;
	m_wcWD.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_wcWD.lpszMenuName = L"Window";
	m_wcWD.lpszClassName = L"ClassName";

	if (!RegisterClassEx(&m_wcWD))
	{
		return false;
	}
	return true;
}
bool Window::Frame()
{
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
	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);
	CenterWindow();
	return true;
}
bool Window::Redner()
{
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
	}
	return true;
}
bool Window::Release()
{
	return true;
}

void Window::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = ((iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2);
	int y = ((iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2);
	MoveWindow(m_hWnd, x, y, m_rtWindow.right - m_rtWindow.left, m_rtWindow.bottom - m_rtWindow.top, true);
}