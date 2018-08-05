#include "Core.h"


bool Core::GameInit()
{
	m_hScreenDC = GetDC(g_hWnd);
	g_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffBitmap = CreateCompatibleBitmap(m_hScreenDC, m_rtClient.right, m_rtClient.bottom);
	SelectObject(g_hOffScreenDC, m_hOffBitmap);

	COLORREF bkColor = RGB(255, 255, 204);
	m_hBkbrush = CreateSolidBrush(bkColor);
	SelectObject(g_hOffScreenDC, m_hBkbrush);

	m_Timer.Init();
	I_Input.Init();
	Init();
	return true;
}
bool Core::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
bool Core::GameRelease()
{
	Release();
	m_Timer.Release();
	I_Input.Release();

	DeleteObject(m_hBkbrush);
	DeleteObject(m_hOffBitmap);
	DeleteDC(g_hOffScreenDC);
	ReleaseDC(g_hWnd, m_hScreenDC);
	return true;
}
bool Core::GameFrame()
{
	Frame();
	m_Timer.Frame();
	I_Input.Frame();
	return true;
}
bool Core::GameRender()
{
	if (GamePreRender())
	{
		Render();
		m_Timer.Render();
		I_Input.Render();
	}
	GamePostRender();
	return true;
}
bool Core::GamePreRender()
{
	PatBlt(g_hOffScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, PATCOPY);
	return true;
}
bool Core::GamePostRender()
{
	BitBlt(m_hScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, g_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}

bool Core::Init()
{
	return true;
}
bool Core::Frame()
{
	return true;
}
bool Core::Render()
{
	return true;
}
bool Core::Release()
{
	return true;
}