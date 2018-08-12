#include "Player.h"

bool Player::Init()
{
	pe.LoadFile(L"PLAYER", L"../02_data/KahoColor.bmp", L"../02_data/KahoMask.bmp");
	pe.Set(500, 500, 50, 74, 48, 48);
	return true;
}
bool Player::Frame()
{
	if (S_Input.GetKey('W') == KEYSTATE::KEY_PUSH ||
		S_Input.GetKey('W') == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos.y += (-1 * g_fPerSecFrame * 1000.f);
	}
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH ||
		S_Input.GetKey('S') == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos.y += (1 * g_fPerSecFrame * 1000.f);
	}
	if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH ||
		S_Input.GetKey('A') == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos.x += (-1 * g_fPerSecFrame * 1000.f);
	}
	if (S_Input.GetKey('D') == KEYSTATE::KEY_PUSH ||
		S_Input.GetKey('D') == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos.x += (1 * g_fPerSecFrame * 1000.f);
	}

	m_DrawPos.x = m_CenterPos.x - (m_rtDraw.right * m_fZoom / 2);
	m_DrawPos.y = m_CenterPos.y - (m_rtDraw.bottom * m_fZoom / 2);

	FLOAT d = m_rtDraw.right * m_fZoom / 2;
	FLOAT e = m_rtDraw.bottom * m_fZoom / 2;

	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - d);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - e);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + d);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + e);
	return true;
}