#include "KahoAttack2.h"

bool KahoAttack2::Init()
{
	m_pEffectSprite = S_SpriteMgr.LoadSprite(L"Kaho", L"Leaf2");
	m_pEffectSprite->setIndex(0);
	m_pEffectSprite->setDivideTime(0.7f);
	Object::Init();
	return true;
}

bool KahoAttack2::Frame()
{
	EffectObj::Frame();
	if (m_pEffectSprite->getIndex() < 4)
	{
		m_rtCollision.left = 0;
		m_rtCollision.right = 0;
		m_rtCollision.bottom = 0;
		m_rtCollision.top = 0;
	}
	return true;
}