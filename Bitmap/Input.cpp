#include "Input.h"

bool Input::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(KEYSTATE) * 256);
	ZeroMemory(m_dwCurrentMouse, sizeof(KEYSTATE) * 256);
	ZeroMemory(m_dwBeforeMouse, sizeof(KEYSTATE) * 256);
	return true;
}
bool Input::Frame()
{
	for (int i = 0; i < 256; ++i)
	{
		m_dwKeyState[i] = KeyCheck(i);
	}
	for (int iButton = 0; iButton < 3; ++iButton)
	{
		if (m_dwBeforeMouse[iButton] == KEYSTATE::KEY_PUSH)
		{
			if (m_dwCurrentMouse[iButton] == KEYSTATE::KEY_PUSH)
				m_dwCurrentMouse[iButton] = KEYSTATE::KEY_HOLD;
		}
		if (m_dwBeforeMouse[iButton] == KEYSTATE::KEY_UP)
		{
			if (m_dwCurrentMouse[iButton] == KEYSTATE::KEY_UP)
				m_dwCurrentMouse[iButton] = KEYSTATE::KEY_FREE;
		}
		m_dwBeforeMouse[iButton] = m_dwCurrentMouse[iButton];
	}
	return true;
}
bool Input::Render()
{
	return true;
}
bool Input::Release()
{
	return true;
}

KEYSTATE Input::getKey(DWORD sKey)
{
	return m_dwKeyState[sKey];
}
KEYSTATE Input::getMouse(DWORD sKey)
{
	return m_dwCurrentMouse[sKey];
}
KEYSTATE Input::KeyCheck(DWORD sKey)
{
	SHORT Key = GetAsyncKeyState(sKey);
	if (Key & 0x8000)
	{
		if (m_dwKeyState[sKey] == KEYSTATE::KEY_FREE ||
			m_dwKeyState[sKey] == KEYSTATE::KEY_UP)
			m_dwKeyState[sKey] = KEYSTATE::KEY_HOLD;
		else
		{
			m_dwKeyState[sKey] = KEYSTATE::KEY_PUSH;
		}
	}
	else
	{
		if (m_dwKeyState[sKey] == KEYSTATE::KEY_HOLD ||
			m_dwKeyState[sKey] == KEYSTATE::KEY_PUSH)
			m_dwKeyState[sKey] = KEYSTATE::KEY_UP;
		else
		{
			m_dwKeyState[sKey] = KEYSTATE::KEY_FREE;
		}
	}
	return m_dwKeyState[sKey];
}