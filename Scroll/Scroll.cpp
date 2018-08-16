#include "Scroll.h"

Scroll::Scroll(Object * pPlayer, Object * pBkObj) : m_pPlayer(pPlayer),
		m_PlayerCollisionRt(pPlayer->getCollisionRt()), m_pBkObj(pBkObj),
		m_BkRtDraw(pBkObj->getrtDraw())
{
}

bool Scroll::Init()
{
	Set(g_rtClient);
	return true;
}
bool Scroll::Frame()
{
	SCROLL type = Collision(m_PlayerCollisionRt);
	if (type == SCROLL::STOP)
	{
		return true;
	}
	MoveCamera(type);
	return true;
}
bool Scroll::Render()
{
	int prevpen = SetROP2(g_hOffScreenDC, R2_NOTXORPEN);

	for (int i = 0; i < 2; ++i)
	{
		Rectangle(g_hOffScreenDC, m_rtCollision[i].left, m_rtCollision[i].top,
			m_rtCollision[i].right, m_rtCollision[i].bottom);
	}

	SetROP2(g_hOffScreenDC, prevpen);
	return true;
}
bool Scroll::Release()
{
	return true;
}
bool Scroll::Set(const RECT& rt)
{
	m_rtCollision[0].left = rt.left;
	m_rtCollision[0].top = rt.top;
	m_rtCollision[0].right = rt.left + 300;
	m_rtCollision[0].bottom = rt.bottom;

	m_CenterPos[0].x = (m_rtCollision[0].left + m_rtCollision[0].right) / 2;
	m_CenterPos[0].y = (m_rtCollision[0].top + m_rtCollision[0].bottom)/ 2;

	m_rtCollision[1].left = rt.right - 300;
	m_rtCollision[1].top = rt.top;
	m_rtCollision[1].right = rt.right;
	m_rtCollision[1].bottom = rt.bottom;

	m_CenterPos[1].x = (m_rtCollision[1].left + m_rtCollision[1].right) / 2;
	m_CenterPos[1].y = (m_rtCollision[1].top + m_rtCollision[1].bottom) / 2;

	return true;
}
SCROLL Scroll::Collision(const RECT& rt)
{
	POINT A_Center;
	A_Center.x = (rt.right + rt.left) / 2;
	A_Center.y = (rt.bottom + rt.top) / 2;


	LONG xDiff = abs(A_Center.x - m_CenterPos[1].x);
	LONG yDiff = abs(A_Center.y - m_CenterPos[1].y);

	if (xDiff < (rt.right - A_Center.x) + ((m_rtCollision[1].right - m_CenterPos[1].x)) &&
		yDiff < (rt.bottom - A_Center.y) + ((m_rtCollision[1].bottom - m_CenterPos[1].y)))
	{
		if (m_BkRtDraw.right - m_BkRtDraw.left == g_rtClient.right)  // 화면 끝 도달
		{
			return SCROLL::STOP;
		}
		return SCROLL::MOVE_RIGHT;
	}

	xDiff = abs(A_Center.x - m_CenterPos[0].x);
	yDiff = abs(A_Center.y - m_CenterPos[0].y);

	if (xDiff < (rt.right - A_Center.x) + ((m_rtCollision[0].right - m_CenterPos[0].x)) &&
		yDiff < (rt.bottom - A_Center.y) + ((m_rtCollision[0].bottom - m_CenterPos[0].y)))
	{
		if (m_BkRtDraw.left == g_rtClient.left)  // 화면 끝 도달
		{
			return SCROLL::STOP;
		}
		return SCROLL::MOVE_LEFT;
	}

	return SCROLL::STOP;
}


void Scroll::MoveCamera(SCROLL type)
{
	switch (type)
	{
	case SCROLL::MOVE_RIGHT:
		m_pBkObj->MoveScrollBk(true);
		m_pPlayer->setCenterPos_x(m_rtCollision[1].left - 38.0f);
		break;
	case SCROLL::MOVE_LEFT:
		m_pBkObj->MoveScrollBk(false);
		m_pPlayer->setCenterPos_x(m_rtCollision[0].right + 38.7f);
		break;
	default:
		break;
	}
}