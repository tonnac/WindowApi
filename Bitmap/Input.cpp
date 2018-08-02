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
		if (m_dwBeforeMouse[iButton] == KEYSTATE::KEY_HOLD)
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
void Input::MsgEvent(MSG msg)
{
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
		m_dwCurrentMouse[0] = KEYSTATE::KEY_PUSH;
		break;
	case WM_LBUTTONUP:
		m_dwCurrentMouse[0] = KEYSTATE::KEY_UP;
		break;
	case WM_MBUTTONDOWN:
		m_dwCurrentMouse[1] = KEYSTATE::KEY_PUSH;
		break;
	case WM_MBUTTONUP:
		m_dwCurrentMouse[1] = KEYSTATE::KEY_UP;
		break;
	case WM_RBUTTONDOWN:
		m_dwCurrentMouse[2] = KEYSTATE::KEY_PUSH;
		break;
	case WM_RBUTTONUP:
		m_dwCurrentMouse[2] = KEYSTATE::KEY_UP;
	}
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