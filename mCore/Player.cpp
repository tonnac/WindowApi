#include "Player.h"

bool Player::Init()
{
	LoadFile(L"PLAYER", L"../02_data/bitmap1.bmp", L"../02_data/bitmap2.bmp");
	Set(500, 500, 133, 1, 42, 59);
	return true;
}
bool Player::Frame()
{
	if (S_Input.GetKey(VK_INSERT) == KEYSTATE::KEY_PUSH)
	{
		if (m_sRotation < 0)
		{
			m_sRotation = TB_ROTATION;
		}
		else
		{
			m_sRotation = -1;
		}
	}
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

	m_DrawPos.x = m_CenterPos.x - (m_rtDraw.right / 2);
	m_DrawPos.y = m_CenterPos.y - (m_rtDraw.bottom / 2);

	m_rtCollision.left = m_DrawPos.x;
	m_rtCollision.top = m_DrawPos.y;
	m_rtCollision.right = m_DrawPos.x + m_rtDraw.right;
	m_rtCollision.bottom = m_DrawPos.y + m_rtDraw.bottom;
	return true;
}