#include "Scroll.h"
#include "Player.h"

Scroll::Scroll(Object * pPlayer, Object * pBkObj) : m_pPlayer(pPlayer),
		m_PlayerCollisionRt(pPlayer->getCollisionRt()), m_pBkObj(pBkObj),
		m_BkRtDraw(pBkObj->getrtDraw())
{
}

bool Scroll::Init()
{
	m_rtCollision[0].left = g_rtClient.left;
	m_rtCollision[0].top = g_rtClient.top;
	m_rtCollision[0].right = g_rtClient.left + 225;
	m_rtCollision[0].bottom = g_rtClient.bottom;

	m_CenterPos[0].x = static_cast<FLOAT>((m_rtCollision[0].left + m_rtCollision[0].right) / 2);
	m_CenterPos[0].y = static_cast<FLOAT>((m_rtCollision[0].top + m_rtCollision[0].bottom) / 2);

	m_rtCollision[1].left = g_rtClient.right - 225;
	m_rtCollision[1].top = g_rtClient.top;
	m_rtCollision[1].right = g_rtClient.right;
	m_rtCollision[1].bottom = g_rtClient.bottom;

	m_CenterPos[1].x = static_cast<FLOAT>((m_rtCollision[1].left + m_rtCollision[1].right) / 2);
	m_CenterPos[1].y = static_cast<FLOAT>((m_rtCollision[1].top + m_rtCollision[1].bottom) / 2);
	return true;
}
bool Scroll::Frame()
{
	Collision(*m_PlayerCollisionRt);
	return true;
}
bool Scroll::Render()
{
	//int prevpen = SetROP2(g_hOffScreenDC, R2_NOTXORPEN);

	//for (int i = 0; i < 2; ++i)
	//{
	//	Rectangle(g_hOffScreenDC, m_rtCollision[i].left, m_rtCollision[i].top,
	//		m_rtCollision[i].right, m_rtCollision[i].bottom);
	//}

	//SetROP2(g_hOffScreenDC, prevpen);
	return true;
}
bool Scroll::Release()
{
	return true;
}
bool Scroll::Collision(const RECT& rt)
{
	LONG x1;
	LONG x2;			//충돌영역 계산
	

	POINT A_Center;
	A_Center.x = (rt.right + rt.left) / 2;
	A_Center.y = (rt.bottom + rt.top) / 2;

	LONG size = rt.right - rt.left;

	LONG xDiff = static_cast<LONG>(abs(A_Center.x - m_CenterPos[1].x));
	LONG yDiff = static_cast<LONG>(abs(A_Center.y - m_CenterPos[1].y));

	if (xDiff < (rt.right - A_Center.x) + ((m_rtCollision[1].right - m_CenterPos[1].x)) &&
		yDiff < (rt.bottom - A_Center.y) + ((m_rtCollision[1].bottom - m_CenterPos[1].y)))
	{
		x1 = (m_rtCollision[1].left < rt.left) ? rt.left : m_rtCollision[1].left;
		x2 = (m_rtCollision[1].right > rt.right) ? rt.right : m_rtCollision[1].right;
		if (m_BkRtDraw->right - m_BkRtDraw->left <= g_rtClient.right)  // 화면 끝 도달
		{
			return true;
		}
		return MoveCamera(x1 - x2 - 2);
	}

	xDiff = static_cast<LONG>(abs(A_Center.x - m_CenterPos[0].x));
	yDiff = static_cast<LONG>(abs(A_Center.y - m_CenterPos[0].y));

	if (xDiff < (rt.right - A_Center.x) + ((m_rtCollision[0].right - m_CenterPos[0].x)) &&
		yDiff < (rt.bottom - A_Center.y) + ((m_rtCollision[0].bottom - m_CenterPos[0].y)))
	{
		x1 = (m_rtCollision[0].left < rt.left) ? rt.left : m_rtCollision[0].left;
		x2 = (m_rtCollision[0].right > rt.right) ? rt.right : m_rtCollision[0].right;
		if (m_BkRtDraw->left == g_rtClient.left)  // 화면 끝 도달
		{
			return true;
		}
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
		if (pl->getDir() == -1)
		{
			return MoveCamera(x2 - x1 + 1);
		}
	}
	return true;
}


bool Scroll::MoveCamera(const LONG& size)
{
	FLOAT x = (*m_pPlayer->getCenterPos()).x;
	m_pPlayer->setCenterPos_x(x + size);
	m_pBkObj->MoveScrollBk(size);
	return true;
}