#include "PlayerBrake.h"

PlayerBrake::PlayerBrake(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Brake"), this);
}
bool PlayerBrake::Init()
{
	setSprite(L"Kaho",L"Brake");
	m_pSprite->setDivideTime(0.55f);
	return true;
}
bool PlayerBrake::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_FREE)
	{
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Idle");
		return true;
	}
	m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}
bool PlayerBrake::Render()
{
	return true;
}
bool PlayerBrake::Release()
{
	return true;
}