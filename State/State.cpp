#include "State.h"
//State::State(Object* pObject) : m_pObject(pObject)
//{}

void State::setSprite(T_STR cName, T_STR szSprite)
{
	m_pSprite = S_SpriteMgr.LoadSprite(cName, szSprite);
}