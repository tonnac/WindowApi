#include "Timer.h"

Timer::Timer()
{
	ZeroMemory(m_csBuffer, sizeof(TCHAR) * 256);
	m_dwBeforeTick = 0;
	m_dwFrameCount = 0;
	m_fTimer = 0.0f;
	m_fSecPerFrame = 0.0f;
	m_fGametime = 0.0f;
	m_dwFPS = 60;
	m_fInterval = (1000.0f / m_dwFPS) /1000.f;
}

bool Timer::Init()
{
	m_dwBeforeTick = timeGetTime();
	return true;
}
bool Timer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD ElapstedTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecPerFrame = ElapstedTick / 1000.0f;
	//if (m_fSecPerFrame < m_fInterval)
	//{
	//	Sleep(m_fInterval - m_fSecPerFrame);
	//	m_fSecPerFrame += m_fInterval - m_fSecPerFrame;
	//}
	m_fTimer += m_fSecPerFrame;
	m_fGametime += m_fSecPerFrame;
	if (m_fTimer >= 1.0f)
	{
		m_fTimer -= 1.0f;
		_stprintf_s(m_csBuffer, L"FPS : %d  Time : %5.5f  SPF : %5.5f", m_dwFrameCount, m_fGametime, m_fSecPerFrame);
		m_dwFrameCount = 0;
	}
	m_dwFrameCount++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
}
bool Timer::Render()
{
	HDC hdc = GetDC(g_hWnd);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 0, 0, m_csBuffer, _tcslen(m_csBuffer));
	ReleaseDC(g_hWnd,hdc);
	return true;
}
bool Timer::Release()
{
	return true;
}