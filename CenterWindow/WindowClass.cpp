#include "WindowClass.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_MBUTTONDOWN:
		DestroyWindow(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

bool Window::setWindow(HINSTANCE hinst)
{
	WNDCLASSEX wd;
	ZeroMemory(&wd, sizeof(WNDCLASSEX));
	wd.cbSize = sizeof(WNDCLASSEX);
	wd.style = CS_VREDRAW | CS_HREDRAW;
	wd.lpfnWndProc = WndProc;
	wd.hInstance = hinst;
	wd.hIcon = LoadIcon(nullptr, IDI_SHIELD);
	wd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wd.lpszMenuName = L"Window";
	wd.lpszClassName = L"Class";
	wd.hIconSm = LoadIcon(nullptr, IDI_ERROR);

	if (!RegisterClassEx(&wd))
	{
		return false;
	}

	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		wd.lpszClassName,
		wd.lpszMenuName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		1024,
		768,
		nullptr,
		nullptr,
		wd.hInstance,
		nullptr);
	
	if (m_hWnd == nullptr)
	{
		return false;
	}

	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);

	CenterWindow();

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}
bool Window::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}
void Window::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = ((iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2);
	int y = ((iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2);
	MoveWindow(m_hWnd, x, y, m_rtWindow.right - m_rtWindow.left, m_rtWindow.bottom, m_rtWindow.top);
}