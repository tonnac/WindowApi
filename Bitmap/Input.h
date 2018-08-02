#pragma once
#include "Std.h"

class Input : public Singleton<Input>
{
	friend class Singleton<Input>;
public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
public:
	KEYSTATE		getKey(DWORD sKey);
	KEYSTATE		m_dwCurrentMouse[3];
	void			MsgEvent(MSG msg);
private:
	KEYSTATE		KeyCheck(DWORD sKey);
private:
	Input() {}
private:
	KEYSTATE		m_dwKeyState[256];
	KEYSTATE		m_dwBeforeMouse[3];
};

#define I_Input Input::getInstance()