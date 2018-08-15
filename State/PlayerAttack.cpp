#include "PlayerAttack.h"

PlayerAttack::PlayerAttack(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pPlayer->addState(std::string("Attack1"), this);
}
bool PlayerAttack::Init()
{
	setSprite(L"Kaho", L"Attack1");
	m_pSprite->setDivideTime(0.7f);
	return true;
}
bool PlayerAttack::Frame()
{
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
		pl->setState(L"Idle");
		return true;
	}
	RECT& rt = m_pPlayer->getrtDraw();
	rt = m_pSprite->getSpriteRt();
	return true;
}
bool PlayerAttack::Render()
{
	return true;
}
bool PlayerAttack::Release()
{
	return true;
}