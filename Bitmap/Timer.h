#pragma once
#include "Std.h"

class Timer
{
public:
	Timer();
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
private:
	TCHAR			m_csBuffer[256];
	DWORD			m_dwBeforeTick;
	DWORD			m_dwFrameCount;
	float			m_fTimer;
	float			m_fSecPerFrame;
	float			m_fGametime;
};