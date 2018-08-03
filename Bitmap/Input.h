#pragma once
#include "Std.h"

class Input : public Singleton<Input>
{
	friend class Singleton<Input>;
public:
	bool				Init();
	bool				Frame();
	bool				Render();
	bool				Release();
	KEYSTATE			getKey(DWORD);
private:
	KEYSTATE			KeyCheck(DWORD);
private:
	Input() {}
private:
	KEYSTATE			m_ksKeyState[256];
};

#define I_Input Input::getInstance()