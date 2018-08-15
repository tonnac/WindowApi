#include "Player.h"
#include "PlayerState.h"

bool Player::Init()
{
	m_pState = new PlayerState(this);
	m_pState->Init();
	Object::Init();
	return true;
}

bool Player::Frame()
{
	m_pState->Frame();
	Object::Frame();
	return true;
}