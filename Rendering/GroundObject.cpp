#include "GroundObject.h"

GroundObject::GroundObject(Player * player) : TerrainObject(player)
{}
bool GroundObject::Frame()
{
	m_rtCollision.left = 0;
	m_rtCollision.top = 562;
	m_rtCollision.right = m_rtDraw.right;
	m_rtCollision.bottom = 700;
	return true;
}
//bool GroundObject::Render()
//{
//	return true;
//}