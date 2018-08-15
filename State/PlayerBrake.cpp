#include "PlayerBrake.h"

PlayerBrake::PlayerBrake(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pPlayer->addState(std::string("Brake"), this);
}
bool PlayerBrake::Init()
{
	setSprite(L"Kaho",L"Brake");
	m_pSprite->setDivideTime(0.7f);
	return true;
}
bool PlayerBrake::Frame()
{
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_FREE)
	{
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
		
	}
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
bool PlayerBrake::Render()
{
	return true;
}
bool PlayerBrake::Release()
{
	return true;
}