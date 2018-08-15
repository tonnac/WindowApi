#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunState.h"
#include "PlayerBrakeState.h"

Player::Player() : m_pCurrentState(nullptr)
{
	m_iCurrentDir = 1;
	State * state = new PlayerState(this);
	m_pStateList.push_back(state);
	state = new PlayerRunState(this);
	m_pStateList.push_back(state);
	state = new PlayerBrakeState(this);
	m_pStateList.push_back(state);
}

bool Player::Init()
{
	for (auto it : m_pStateList)
	{
		it->Init();
	}
	m_pCurrentState = m_pStateList[0];
	Object::Init();
	return true;
}

bool Player::Frame()
{
	m_pCurrentState->Frame();
	Object::Frame();
	return true;
}

void Player::setIdle()
{
	m_pCurrentState = m_pStateList[0];
}
void Player::setBrake()
{
	m_pCurrentState = m_pStateList[2];
}
void Player::setRun()
{
	m_pCurrentState = m_pStateList[1];
}
INT	Player::getDir()
{
	return m_iCurrentDir;
}
void Player::setDir(const INT& dir)
{
	m_iCurrentDir *= dir;
}