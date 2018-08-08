#include "NPCObj.h"

bool NPCObj::Frame()
{
	int iHalfX = m_rtDraw.right / 2;
	int iHalfY = m_rtDraw.bottom / 2;

	if (m_CenterPos.x - iHalfX < g_rtClient.left)
	{
		m_fDir[0] *= -1;
		m_CenterPos.x = g_rtClient.left + iHalfX;
	}
	if (m_CenterPos.x + iHalfX > g_rtClient.right)
	{
		m_fDir[0] *= -1;
		m_CenterPos.x = g_rtClient.right - iHalfX;
	}
	if (m_CenterPos.y - iHalfY < g_rtClient.top)
	{
		m_fDir[1] *= -1;
		m_CenterPos.y = g_rtClient.top + iHalfY;
	}
	if (m_CenterPos.y + iHalfY > g_rtClient.bottom)
	{
		m_fDir[1] *= -1;
		m_CenterPos.y = g_rtClient.bottom - iHalfY;
	}
	m_CenterPos.x += (m_fDir[0] * g_fSecPerFrame * m_fSpeed);
	m_CenterPos.y += (m_fDir[1] * g_fSecPerFrame * m_fSpeed);
	m_DrawPos.x = m_CenterPos.x - (m_rtDraw.right / 2);
	m_DrawPos.y = m_CenterPos.y - (m_rtDraw.bottom / 2);
	m_rtCollision.left = m_DrawPos.x;
	m_rtCollision.top = m_DrawPos.y;
	m_rtCollision.right = m_DrawPos.x + m_rtDraw.right;
	m_rtCollision.bottom = m_DrawPos.y + m_rtDraw.bottom;

	return true;
}

NPCObj::NPCObj()
{
	m_fSpeed = (rand() % 150) + 70;
}