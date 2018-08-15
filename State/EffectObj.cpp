#include "EffectObj.h"

bool EffectObj::Init()
{
	return true;
}
bool EffectObj::Frame()
{
	if (!m_pEffectSprite->Frame())
	{
		m_pEffectSprite->setIndex(0);
	}
	m_rtDraw = m_pEffectSprite->getSpriteRt();
	Object::Frame();
	return true;
}

void EffectObj::setSprite(Sprite* sprite)
{
	if (m_pEffectSprite)
	{
		delete m_pEffectSprite;
		m_pEffectSprite = nullptr;
	}
	m_pEffectSprite = sprite;
}