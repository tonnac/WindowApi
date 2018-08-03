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
		m_ksKeyState[dwKey] = KEYSTATE::KEY_PUSH;
	}
	else if (Key & 0x8001)
	{
		m_ksKeyState[dwKey] = KEYSTATE::KEY_HOLD;
	}
	else if (Key & 0x0001)
	{
		m_ksKeyState[dwKey] = KEYSTATE::KEY_UP;
	}
	else
		m_ksKeyState[dwKey] = KEYSTATE::KEY_FREE;
	return m_ksKeyState[dwKey];
}
