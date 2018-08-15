#include "PlayerState.h"

PlayerState::PlayerState(Object * pObject) : State(pObject)
{}

bool PlayerState::Init()
{
	setSprite(L"Idle");
	return true;
}
bool PlayerState::Frame()
{
	RECT& rt = m_pObject->getrtDraw();
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