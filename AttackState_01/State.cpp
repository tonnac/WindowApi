#include "State.h"
State::State(Object* pObject) : m_pObject(pObject), m_CenterPos(pObject->getCenterPos()),
m_DrawPos(pObject->getDrawPos()), m_rtCollision(pObject->getCollisionRt()), m_rtDraw(pObject->getrtDraw())
{}

void State::setSprite(T_STR cName, T_STR szSprite)
{
	m_pSprite = S_SpriteMgr.LoadSprite(cName, szSprite);
}