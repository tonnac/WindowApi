#include "Player.h"

bool Player::Init()
{
	m_pRendering = New InversionRendering(this, 2.8f, ZOOM);
	m_pRendering->Init();
	return true;
}
bool Player::Frame()
{
	Object::Frame();
	return true;
}
//bool Player::Render()
//{
//
//}
bool Player::Release()
{
	return true;
}