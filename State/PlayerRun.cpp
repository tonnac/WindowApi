#include "PlayerRun.h"

PlayerRun::PlayerRun(Player * pPlayer) : PlayerState(pPlayer)
{
	m_pPlayer->addState(std::string("Run"), this);
}
bool PlayerRun::Init()
{
	setSprite(L"Kaho",L"Run");
	return true;
}
bool PlayerRun::Frame()
{
	if ((m_pPlayer->getDir() == 1 && (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD))
		||(m_pPlayer->getDir() == -1 && (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)))
	{
		RECT& rt = m_pPlayer->getrtDraw();
		rt = m_pSprite->getSpriteRt();
	}
	else if ((S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_FREE) ||
		(S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_FREE))
	{
		m_pSprite->setIndex(0);
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
		pl->setState(L"Brake");
		return true;
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(2);
	}

	return true;
}
bool PlayerRun::Render()
{
	return true;
}
bool PlayerRun::Release()
{
	return true;
}