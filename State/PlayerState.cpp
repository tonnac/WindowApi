#include "PlayerState.h"

PlayerState::PlayerState(Player * pPlayer) : m_pPlayer(pPlayer)
{}

bool PlayerState::Init()
{
	setSprite(L"Idle");
	return true;
}
bool PlayerState::Frame()
{
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pPlayer->getDir() == -1)
		{
			m_pPlayer->setRun();
		}
		else
		{
			m_pPlayer->setDir(-1);
			m_pPlayer->setRendering(INVERSE::LR_ROTATION);
			m_pPlayer->setRun();
		}
	}
	if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pPlayer->getDir() == 1)
		{
			m_pPlayer->setRun();
		}
		else
		{
			m_pPlayer->setDir(-1);
			m_pPlayer->setRendering(INVERSE::DEFAULT);
			m_pPlayer->setRun();
		}
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
	}
	RECT& rt = m_pPlayer->getrtDraw();
	rt = m_pSprite->getSpriteRt();
	return true;
}
bool PlayerState::Render()
{
	return true;
}
bool PlayerState::Release()
{
	return true;
}