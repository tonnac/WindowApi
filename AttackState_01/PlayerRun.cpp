#include "PlayerRun.h"

PlayerRun::PlayerRun(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Run"), this);
}
bool PlayerRun::Init()
{
	setSprite(L"Kaho",L"Run");
	return true;
}
bool PlayerRun::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pPlayer->setState(L"Attack1");
	}
	if ((m_pPlayer->getDir() == 1 && (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_HOLD))
		||(m_pPlayer->getDir() == -1 && (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)))
	{
		m_CenterPos.x += m_pPlayer->getDir() * g_fPerSecFrame * 200.0f;
		m_rtDraw = m_pSprite->getSpriteRt();
	}
	else if ((S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_FREE) ||
		(S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_UP || S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_FREE))
	{
		m_pSprite->setIndex(0);
		m_pPlayer->setState(L"Brake");
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