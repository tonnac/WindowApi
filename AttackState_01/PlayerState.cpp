#include "PlayerState.h"

PlayerState::PlayerState(Player * pPlayer) : State(pPlayer), m_pEffectObj(nullptr)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Idle"), this);
}

bool PlayerState::Init()
{
	setSprite(L"Kaho",L"Idle");
	return true;
}
bool PlayerState::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH || S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
	{
		if (m_pPlayer->getDir() == -1)		//���� ������
		{
			m_pPlayer->setState(L"Run");
		}
		else								//���� �ٸ���
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
	if (!m_pSprite->Frame())				//�ѹ��� �ٵ���
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
	return true;
}