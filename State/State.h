#pragma once
#include "SpriteMgr.h"
#include "Player.h"

class State
{
public:
	State(Player*);
public:
	virtual bool		Init() = 0;
	virtual bool		Frame() = 0;
	virtual bool		Render() = 0;
	virtual bool		Release() = 0;
public:
	void				setSprite(T_STR);
private:
	Sprite *			m_pSprite;
	Player *			m_pPlayer;
};