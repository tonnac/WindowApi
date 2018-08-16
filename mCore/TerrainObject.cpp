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
bool TerrainObject::Render()
{
	int prevpen = SetROP2(g_hOffScreenDC, R2_NOTXORPEN);

	Rectangle(g_hOffScreenDC, m_rtCollision.left, m_rtCollision.top,
		m_rtCollision.right, m_rtCollision.bottom);

	SetROP2(g_hOffScreenDC, prevpen);
	return true;
}
bool TerrainObject::Release()
{
	return true;
}
bool TerrainObject::Collision(Object* pObject)
{
	RECT ColiisionRT = *(pObject->getCollisionRt());
	POINT A_Center;
	A_Center.x = (ColiisionRT.right + ColiisionRT.left) / 2;
	A_Center.y = (ColiisionRT.bottom + ColiisionRT.top) / 2;


	LONG xDiff = static_cast<LONG>(abs(A_Center.x - m_CenterPos.x));
	LONG yDiff = static_cast<LONG>(abs(A_Center.y - m_CenterPos.y));

	if (xDiff <= (ColiisionRT.right - A_Center.x) + ((m_rtCollision.right - m_CenterPos.x)) &&
		yDiff <= (ColiisionRT.bottom - A_Center.y) + ((m_rtCollision.bottom - m_CenterPos.y)))
	{
		return MoveObject(pObject);
	}
	return false;
}
bool TerrainObject::MoveObject(Object* pObject)
{
	FloatPoint pObjCenterPos = *(pObject->getCenterPos());
	FLOAT ypos = pObjCenterPos.y - 0.5f;
	pObject->setCenterPos_y(ypos);
	pObject->setLanding(true);
	return true;
}