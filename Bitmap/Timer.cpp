#include "Timer.h"

float g_fSecPerFrame = 0.0f;

Timer::Timer()
{
	ZeroMemory(m_csBuffer, sizeof(TCHAR) * 256);
	m_dwFrameCount = 0;
	m_dwBeforeTick = 0;
	m_fSecPerFrame = 0.0f;
	m_fGameTime = 0.0f;
	m_fTimer = 0.0f;
}

bool Timer::Init()
{
	m_dwBeforeTick = timeGetTime();
	return true;
}
bool Timer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapstedTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecPerFrame = dwElapstedTick / 1000.0f;
	g_fSecPerFrame = m_fSecPerFrame;
	m_fGameTime += m_fSecPerFrame;
	m_fTimer += m_fSecPerFrame;
	if (m_fTimer >= 1.0f)
	{
		m_fTimer -= 1.0f;
		_stprintf_s(m_csBuffer, L"FPS : %d   Time : %3.2f", m_dwFrameCount, m_fGameTime);
		//OutputDebugString(m_csBuffer);
		m_dwFrameCount = 0;
	}
	m_dwFrameCount++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
}
bool Timer::Render()
{
	HDC hdc = GetDC(g_hWnd);
	TextOut(hdc, 0, 0, m_csBuffer, (int)wcslen(m_csBuffer));
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255));

	ReleaseDC(g_hWnd, hdc);
	return true;
}
bool Timer::Release()
{
	return true;
}