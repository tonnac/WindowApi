#include "PlayerBasicState.h"
#include "EffectObj.h"

PlayerState::PlayerState(Player * pPlayer) : State(pPlayer), m_pEffectObj(nullptr)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Idle"), this);
}

bool PlayerState::Init()
{
	setSprite(L"Kaho", L"Idle");
	return true;
}
bool PlayerState::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
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
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pPlayer->setState(L"Attack1");
	}
	if (!m_pSprite->Frame())				//한바퀴 다돌면
	{
		m_pSprite->setIndex(0);
	}
	m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}
bool PlayerState::Render()
{
	return true;
}
bool PlayerState::Release()
{
	if (m_pEffectObj)
	{
		m_pEffectObj->Release();
		delete m_pEffectObj;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////

PlayerRun::PlayerRun(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Run"), this);
}
bool PlayerRun::Init()
{
	setSprite(L"Kaho", L"Run");
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
		|| (m_pPlayer->getDir() == -1 && (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)))
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

//////////////////////////////////////////////////////////////////////////

PlayerBrake::PlayerBrake(Player * pPlayer) : PlayerState(pPlayer)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Brake"), this);
}
bool PlayerBrake::Init()
{
	setSprite(L"Kaho", L"Brake");
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

//////////////////////////////////////////////////////////////////////////

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