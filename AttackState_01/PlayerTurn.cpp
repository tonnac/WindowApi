#include "PlayerTurn.h"

PlayerTurn::PlayerTurn(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Turn"), this);
}
bool PlayerTurn::Init()
{
	setSprite(L"Kaho", L"Turn");
	m_pSprite->setDivideTime(0.25f);
	return true;
}
bool PlayerTurn::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	if (!m_pSprite->Frame())
	{
		m_pPlayer->setDir(-1);
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Run");
		return true;
	}
	if (m_pPlayer->getDir() == 1)
	{
		m_pPlayer->setRendering(INVERSE::LR_ROTATION);
	}
	else
	{
		m_pPlayer->setRendering(INVERSE::DEFAULT);
	}
	m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}
bool PlayerTurn::Render()
{
	return true;
}
bool PlayerTurn::Release()
{
	return true;
}