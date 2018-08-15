#include "PlayerBrakeState.h"

PlayerBrakeState::PlayerBrakeState(Player * pPlayer) : PlayerState(pPlayer)
{}
bool PlayerBrakeState::Init()
{
	setSprite(L"Brake");
	m_pSprite->setDivideTime(0.7f);
	return true;
}
bool PlayerBrakeState::Frame()
{
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_FREE)
	{
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
		
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
		pl->setIdle();
		return true;
	}
	RECT& rt = m_pPlayer->getrtDraw();
	rt = m_pSprite->getSpriteRt();
	return true;
}
bool PlayerBrakeState::Render()
{
	return true;
}
bool PlayerBrakeState::Release()
{
	return true;
}