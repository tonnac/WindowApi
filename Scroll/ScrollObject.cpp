#include "ScrollObject.h"

bool ScrollObject::Init()
{
	Set(g_rtClient);
	return true;
}
bool ScrollObject::Frame()
{
	return true;
}
bool ScrollObject::Render()
{
	int prevpen = SetROP2(g_hOffScreenDC, R2_MASKPEN);

	for (int i = 0; i < 2; ++i)
	{
		Rectangle(g_hOffScreenDC, m_rtCollision[i].left, m_rtCollision[i].top,
			m_rtCollision[i].right, m_rtCollision[i].bottom);
	}

	SetROP2(g_hOffScreenDC, prevpen);
	return true;
}
bool ScrollObject::Release()
{
	return true;
}
bool ScrollObject::Set(const RECT& rt)
{
	/*m_DrawPos[0].x = rt.left;
	m_DrawPos[0].y = rt.top;
	m_DrawPos[1].x = rt.right - 300;
	m_DrawPos[2].x = rt.top;*/

	m_rtDraw[0].left = rt.left;
	m_rtDraw[0].top = rt.top;
	m_rtDraw[0].right = rt.left + 300;
	m_rtDraw[0].bottom = rt.bottom;

	m_CenterPos[0].x = (m_rtDraw[0].left + m_rtDraw[0].right) / 2;
	m_CenterPos[0].y = (m_rtDraw[0].top + m_rtDraw[0].bottom)/ 2;

	m_rtDraw[1].left = rt.right - 300;
	m_rtDraw[1].top = rt.top;
	m_rtDraw[1].right = rt.right;
	m_rtDraw[1].bottom = rt.bottom;

	m_CenterPos[1].x = (m_rtDraw[1].left + m_rtDraw[1].right) / 2;
	m_CenterPos[1].y = (m_rtDraw[1].top + m_rtDraw[1].bottom) / 2;

	m_rtCollision[0] = m_rtDraw[0];
	m_rtCollision[1] = m_rtDraw[1];

	return true;
}
INT ScrollObject::Collision(const RECT& rt)
{
	POINT A_Center;
	A_Center.x = (rt.right + rt.left) / 2;
	A_Center.y = (rt.bottom + rt.top) / 2;


	LONG xDiff = abs(A_Center.x - m_CenterPos[1].x);
	LONG yDiff = abs(A_Center.y - m_CenterPos[1].y);

	if (xDiff <= (rt.right - A_Center.x) + ((m_rtCollision[1].right - m_CenterPos[1].x)) &&
		yDiff <= (rt.bottom - A_Center.y) + ((m_rtCollision[1].bottom - m_CenterPos[1].y)))
		return 1;

	xDiff = abs(A_Center.x - m_CenterPos[0].x);
	yDiff = abs(A_Center.y - m_CenterPos[0].y);

	if (xDiff <= (rt.right - A_Center.x) + ((m_rtCollision[0].right - m_CenterPos[0].x)) &&
		yDiff <= (rt.bottom - A_Center.y) + ((m_rtCollision[0].bottom - m_CenterPos[0].y)))
		return 2;

	return 0;
}