#include "Win.h"

HINSTANCE				g_hInstance;
HWND						g_hWnd;


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

bool Window::SetWindow()
{
	g_hInstance = m_hInstance;
	m_wdWindowClass.cbSize = sizeof(WNDCLASSEX);
	m_wdWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	m_wdWindowClass.lpfnWndProc = WndProc;
	m_wdWindowClass.hInstance = m_hInstance;
	m_wdWindowClass.lpszMenuName = L"QWE";
	m_wdWindowClass.lpszClassName = L"WINDOW";

	if (!RegisterClassEx(&m_wdWindowClass))
	{
		return false;
	}

	AdjustWindowRect(&m_rtClient, WS_OVERLAPPEDWINDOW, false);

	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		m_wdWindowClass.lpszClassName,
		m_wdWindowClass.lpszMenuName,
		WS_OVERLAPPEDWINDOW,
		0, 0,
		m_rtClient.right - m_rtClient.left,
		m_rtClient.bottom - m_rtClient.top,
		nullptr,
		nullptr,
		m_hInstance,
		nullptr);

	assert(m_hWnd != nullptr);

	g_hWnd = m_hWnd;

	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);

	CenterWindow();
	return true;
}
bool Window::Run()
{
	GameInit();
	ShowWindow(m_hWnd, SW_SHOW);

	while (m_mMsg.message != WM_QUIT)
	{
		if (PeekMessage(&m_mMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_mMsg);
			DispatchMessage(&m_mMsg);
		}
		else
		{
			GameFrame();
			GameRender();
		}
	}
	return GameRelease();
}
bool Window::GameInit()
{
	return true;
}
bool Window::GameFrame()
{
	return true;
}
bool Window::GameRender()
{
	return true;
}
bool Window::GameRelease()
{
	return true;
}
bool Window::Init()
{
	return true;
}
bool Window::Frame()
{
	return true;
}
bool Window::Render()
{
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
	int x = (iScreenWidth - (m_rtClient.right - m_rtClient.left)) / 2;
	int y = (iScreenHeight - (m_rtClient.bottom - m_rtClient.top)) / 2;
	MoveWindow(m_hWnd, x, y, m_rtClient.right, m_rtClient.bottom, true);
}
Window::Window(HINSTANCE hinst, LONG right, LONG bottom) : m_hInstance(hinst)
{
	m_hInstance = hinst;
	ZeroMemory(&m_wdWindowClass, sizeof(WNDCLASSEX));
	ZeroMemory(&m_mMsg, sizeof(MSG));
	m_rtClient.right = right;
	m_rtClient.bottom = bottom;
}