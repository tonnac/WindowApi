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
	KEYSTATE		getMouse(DWORD sKey);
private:
	KEYSTATE		KeyCheck(DWORD sKey);
private:
	Input() {}
private:
	KEYSTATE		m_dwKeyState[256];
	KEYSTATE		m_dwBeforeMouse[3];
	KEYSTATE		m_dwCurrentMouse[3];
};

#define I_Input Input::getInstance()