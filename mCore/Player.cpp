#include "Player.h"
#include "PlayerAttack.h"
#include "PlayerBasicState.h"

float g_fSpeed = 0.0f;

Player::Player() : m_pCurrentState(nullptr), m_iCurrentDir(1), m_iJumpNumber(0)
{
	State * state = New PlayerIdle(this);
	state = New PlayerRun(this);
	state = New PlayerBrake(this);
	state = New PlayerTurn(this);
	state = New PlayerAttack(this);
	state = New PlayerAttack2(this);
	state = New PlayerAttack3(this);
	state = New PlayerJump(this);
	state = New PlayerJump2(this);
	state = New PlayerFall(this);
	state = New AirAttack(this);
	m_fSpeed = 150.0f;
}

bool Player::Init()
{
	for (auto it : m_pStateList)
	{
		it.second->Init();
	}
	g_fSpeed = m_fSpeed;
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

bool Player::Release()
{
	for (auto it : m_pStateList)
	{
		it.second->Release();
		delete it.second;
	}
	m_pStateList.clear();
	Object::Release();
	return true;
}
bool Player::Render()
{
	Object::Render();
	m_pCurrentState->Render();
	return true;
}
void Player::setState(T_STR szStateName)
{
	std::string cstate(szStateName.begin(), szStateName.end());
	m_pCurrentState = m_pStateList[cstate];
}
void Player::setJumpNum(const INT& Num)
{
	m_iJumpNumber = Num;
}
INT Player::getJumpNum()
{
	return m_iJumpNumber;
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