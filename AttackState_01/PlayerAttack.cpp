#include "PlayerAttack.h"
#include "KahoAttack1.h"

PlayerAttack::PlayerAttack(Player * pPlayer) : PlayerState(pPlayer), m_fTimer(0.0f)
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_pPlayer->addState(std::string("Attack1"), this);
	m_pEffectObj = new KahoAttack1;
}
bool PlayerAttack::Init()
{
	setSprite(L"Kaho", L"Attack1");
	m_pSprite->setDivideTime(0.7f);
	m_pEffectObj->LoadFile(L"PLAYER", L"../02_data/bmp/KahoColor.bmp", L"../02_data/bmp/KahoMask.bmp");
	m_pEffectObj->Init();
	m_pEffectObj->setRendering(2.8f, INVERSE::DEFAULT);
	return true;
}
bool PlayerAttack::Frame()
{
	Player * m_pPlayer = dynamic_cast<Player*>(m_pObject);
	m_CenterPos.x += m_pPlayer->getDir() * g_fPerSecFrame * 50.0f;

	m_pEffectObj->setDebugmode(m_pObject->getDebugmode());
	m_fTimer += g_fPerSecFrame;
	FloatPoint pt;
	if (m_pPlayer->getDir() == -1)
	{
		m_pEffectObj->setRendering(2.8f, INVERSE::LR_ROTATION);
		pt.x = m_CenterPos.x - 75.0f;
		pt.y = m_CenterPos.y;
	}
	else
	{
		m_pEffectObj->setRendering(2.8f, INVERSE::DEFAULT);
		pt.x = m_CenterPos.x + 75.0f;
		pt.y = m_CenterPos.y;
	}
	if (m_fTimer >= 0.4f && S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
	{
		m_pSprite->setIndex(0);
		m_pEffectObj->setIndex(0);
		m_pPlayer->setState(L"Attack2");
		m_fTimer = 0.0f;
	}
	m_pEffectObj->Frame();
	m_pEffectObj->setDrawPos(pt);
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		m_pEffectObj->setIndex(0);
		m_pPlayer->setState(L"Idle");
		m_fTimer = 0.0f;
		return true;
	}
	m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}
bool PlayerAttack::Render()
{
	m_pEffectObj->Render();
	return true;
}
bool PlayerAttack::Release()
{
	return true;
}