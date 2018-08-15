#include "PlayerRunState.h"

PlayerRunState::PlayerRunState(Player * pPlayer) : PlayerState(pPlayer)
{}
bool PlayerRunState::Init()
{
	setSprite(L"Run");
	return true;
}
bool PlayerRunState::Frame()
{
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH ||
		S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		RECT& rt = m_pPlayer->getrtDraw();
		rt = m_pSprite->getSpriteRt();
	}
	else if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_FREE)
	{
		m_pSprite->setIndex(0);
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
		pl->setBrake();
		return true;
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(2);
	}

	return true;
}
bool PlayerRunState::Render()
{
	return true;
}
bool PlayerRunState::Release()
{
	return true;
}