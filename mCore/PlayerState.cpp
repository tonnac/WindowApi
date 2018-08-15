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
		if (m_pPlayer->getDir() == -1)		//방향 같으면
		{
			m_pPlayer->setState(L"Run");
		}
		else								//방향 다르면
		{
			m_pPlayer->setState(L"Turn");
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
			m_pPlayer->setState(L"Turn");
		}
	}
	if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH)
	{
		m_pPlayer->setState(L"Attack1");
	}
	if (!m_pSprite->Frame())				//한바퀴 다돌면
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