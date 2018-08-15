#include "State.h"
State::State(Player* pPlayer) : m_pPlayer(pPlayer)
{}

void State::setSprite(T_STR szSprite)
{
	m_pSprite = S_SpriteMgr.LoadSprite(szSprite);
}