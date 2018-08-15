#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunState.h"
#include "PlayerBrakeState.h"

Player::Player() : m_pCurrentState(nullptr)
{
	m_iCurrentDir = 1;
	State * state = new PlayerState(this);
	state = new PlayerRunState(this);
	state = new PlayerBrakeState(this);
}

bool Player::Init()
{
	for (auto it : m_pStateList)
	{
		it.second->Init();
	}
	m_pCurrentState = m_pStateList["Idle"];
	Object::Init();
	return true;
}

bool Player::Frame()
{
	m_pCurrentState->Frame();
	Object::Frame();
	return true;
}

void Player::setState(T_STR szStateName)
{
	std::string cstate(szStateName.begin(), szStateName.end());
	m_pCurrentState = m_pStateList[cstate];
}
INT	Player::getDir()
{
	return m_iCurrentDir;
}
void Player::setDir(const INT& dir)
{
	m_iCurrentDir *= dir;
}
void Player::addState(std::string Name, State* state)
{
	m_pStateList.insert(std::make_pair(Name, state));
}