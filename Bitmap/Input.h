#pragma once
#include "Std.h"

class Input
{
public:
	bool				Init();
	bool				Frame();
	bool				Render();
	bool				Release();
	KEYSTATE			getKey(DWORD);
private:
	KEYSTATE			KeyCheck(DWORD);
private:
	KEYSTATE			m_ksKeyState[256];
};