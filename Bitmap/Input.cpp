#include "Input.h"

bool Input::Init()
{
	ZeroMemory(m_ksKeyState, sizeof(KEYSTATE) * 256);
	return true;
}
bool Input::Frame()
{
	for (int i = 0; i < 256; ++i)
	{
		m_ksKeyState[i] = KeyCheck(i);
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
