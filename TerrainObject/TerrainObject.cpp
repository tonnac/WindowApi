#include "TerrainObject.h"

bool TerrainObject::Init()
{
	return true;
}
bool TerrainObject::Frame()
{
	m_CenterPos.x = m_DrawPos.x + (m_rtDraw.right /2);
	m_CenterPos.y = m_DrawPos.y + (m_rtDraw.bottom / 2);

	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - m_rtDraw.right / 2);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - m_rtDraw.bottom / 2);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + m_rtDraw.right / 2);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + m_rtDraw.bottom / 2);
	return true;
}
bool TerrainObject::Release()
{
	return true;
}
INT TerrainObject::Collision(const RECT& rt)
{
	POINT A_Center;
	A_Center.x = (rt.right + rt.left) / 2;
	A_Center.y = (rt.bottom + rt.top) / 2;


	LONG xDiff = abs(A_Center.x - m_CenterPos.x);
	LONG yDiff = abs(A_Center.y - m_CenterPos.y);

	if (xDiff <= (rt.right - A_Center.x) + ((m_rtCollision.right - m_CenterPos.x)) &&
		yDiff <= (rt.bottom - A_Center.y) + ((m_rtCollision.bottom - m_CenterPos.y)))
		return 1;
	return 0;
}