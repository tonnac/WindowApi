#pragma once
#include "State.h"
#include "Player.h"

class PlayerState : public State
{
public:
	PlayerState(Player*);
public:
	bool		Init		() override;
	bool		Frame		() override;
	bool		Render		() override;
	bool		Release		() override;
protected:
	Player * m_pPlayer;
};