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
public:
	KEYSTATE			getKey(DWORD);
	KEYSTATE			getMouse(DWORD);
	void				MsgEvent(MSG);
private:
	KEYSTATE			KeyCheck(DWORD);
private:
	Input() {}
private:
	KEYSTATE			m_ksKeyState[256];
	KEYSTATE			m_ksBeforeMouseState[3];
	KEYSTATE			m_ksCurrentMouseState[3];
};

#define I_Input Input::getInstance()