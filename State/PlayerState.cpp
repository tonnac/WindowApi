#include "PlayerState.h"

PlayerState::PlayerState(Player * pPlayer) : m_pPlayer(pPlayer)
{
	m_pPlayer->addState(std::string("Idle"), this);
}

bool PlayerState::Init()
{
	setSprite(L"Kaho",L"Idle");
	return true;
}
bool PlayerState::Frame()
{
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pPlayer->getDir() == -1)
		{
			m_pPlayer->setState(L"Run");
		}
		else
		{
			m_pPlayer->setDir(-1);
			m_pPlayer->setRendering(INVERSE::LR_ROTATION);
			m_pPlayer->setState(L"Run");
		}
	}
	if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pPlayer->getDir() == 1)
		{
			m_pPlayer->setState(L"Run");
		}
		else
		{
			m_pPlayer->setDir(-1);
			m_pPlayer->setRendering(INVERSE::DEFAULT);
			m_pPlayer->setState(L"Run");
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