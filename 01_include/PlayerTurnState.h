#pragma once
#include "PlayerState.h"

class PlayerTurnState : public PlayerState
{
public:
	PlayerTurnState(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
	bool		Release() override;
private:

};