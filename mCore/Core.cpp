#include "Core.h"

HDC			g_hOffScreenDC = nullptr;
HDC			g_hScreenDC = nullptr;
int			g_iNewCount = 0;
MEM_MAP		MemoryMap;

bool Core::GameInit()
{
	m_hScreenDC = g_hScreenDC = GetDC(g_hWnd);
	m_hOffScreenDC = g_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_bkBrush = CreateSolidBrush(RGB(0, 0, 0));
	m_hPen = CreatePen(BS_SOLID, 1, RGB(255, 0, 0));
	HBITMAP hoffbitmap = CreateCompatibleBitmap(m_hScreenDC, g_rtClient.right, g_rtClient.bottom);
	SelectObject(m_hOffScreenDC, hoffbitmap);
	SelectObject(m_hOffScreenDC, m_bkBrush);
	SelectObject(m_hOffScreenDC, m_hPen);

	m_Timer.Init();
	S_Input.Init();
	Init();
	return true;
}
bool Core::GameFrame()
{
	m_Timer.Frame();
	S_Input.Frame();
	Frame();
	return true;
}
bool Core::GameRender()
{
	if (GamePreRender())
	{
		Render();
		m_Timer.Render();
		S_Input.Render();
	}
	GamePostRender();
	return true;
}
bool Core::GameRelease()
{
	DeleteDC(m_hOffScreenDC);
	ReleaseDC(g_hWnd, m_hScreenDC);
	DeleteObject(m_bkBrush);
	DeleteObject(m_hPen);

	m_Timer.Release();
	S_Input.Release();
	Release();
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
bool Core::GamePreRender()
{
	PatBlt(m_hOffScreenDC, 0, 0, g_rtClient.right, g_rtClient.bottom, PATCOPY);
	return true;
}
bool Core::GamePostRender()
{
	BitBlt(m_hScreenDC, 0, 0, g_rtClient.right, g_rtClient.bottom, m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}

