#include "Input.h"

bool Input::Init()
{
	ZeroMemory(m_ksKeyState, sizeof(KEYSTATE) * 256);
	ZeroMemory(m_ksBeforeMouseState, sizeof(KEYSTATE) * 3);
	ZeroMemory(m_ksCurrentMouseState, sizeof(KEYSTATE) * 3);
	return true;
}
bool Input::Frame()
{
	for (int i = 0; i < 256; ++i)
	{
		m_ksKeyState[i] = KeyCheck(i);
	}
	for (int iButton = 0; iButton < 3; ++iButton)
	{
		if (m_ksCurrentMouseState[iButton] == KEYSTATE::KEY_PUSH)
		{
			if (m_ksBeforeMouseState[iButton] == KEYSTATE::KEY_PUSH)
			{
				m_ksCurrentMouseState[iButton] = KEYSTATE::KEY_HOLD;
			}
		}
		if (m_ksCurrentMouseState[iButton] == KEYSTATE::KEY_UP)
		{
			if (m_ksBeforeMouseState[iButton] == KEYSTATE::KEY_UP)
			{
				m_ksCurrentMouseState[iButton] = KEYSTATE::KEY_FREE;
			}
		}
		m_ksBeforeMouseState[iButton] = m_ksCurrentMouseState[iButton];
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

KEYSTATE Input::getKey(DWORD dwKey)
{
	return m_ksKeyState[dwKey];
}
KEYSTATE Input::getMouse(DWORD dwKey)
{
	return m_ksCurrentMouseState[dwKey];
}
void Input::MsgEvent(MSG msg)
{
	switch (msg.message)
	{
	case WM_LBUTTONUP:
		m_ksCurrentMouseState[1] = KEYSTATE::KEY_UP;
		break;
	case WM_LBUTTONDOWN:
		m_ksCurrentMouseState[1] = KEYSTATE::KEY_PUSH;
		break;
	case WM_MBUTTONUP:
		m_ksCurrentMouseState[0] = KEYSTATE::KEY_UP;
		break;
	case WM_MBUTTONDOWN:
		m_ksCurrentMouseState[0] = KEYSTATE::KEY_PUSH;
		break;
	case WM_RBUTTONUP:
		m_ksCurrentMouseState[2] = KEYSTATE::KEY_UP;
		break;
	case WM_RBUTTONDOWN:
		m_ksCurrentMouseState[2] = KEYSTATE::KEY_PUSH;
		break;
	}
}

KEYSTATE Input::KeyCheck(DWORD dwKey)
{
	SHORT Key = GetAsyncKeyState(dwKey);
	if (Key & 0x8000)
	{
		if (m_ksKeyState[dwKey] == KEYSTATE::KEY_UP ||
			m_ksKeyState[dwKey] == KEYSTATE::KEY_FREE)
			m_ksKeyState[dwKey] = KEYSTATE::KEY_PUSH;
		else
			m_ksKeyState[dwKey] = KEYSTATE::KEY_HOLD;
	}
	else
	{
		if (m_ksKeyState[dwKey] == KEYSTATE::KEY_HOLD ||
			m_ksKeyState[dwKey] == KEYSTATE::KEY_PUSH)
			m_ksKeyState[dwKey] = KEYSTATE::KEY_UP;
		else
			m_ksKeyState[dwKey] = KEYSTATE::KEY_FREE;
	}
	return m_ksKeyState[dwKey];
}
