#pragma once
#include "PlayerState.h"

class PlayerTurn : public PlayerState
{
public:
	PlayerTurn(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
	bool		Release() override;
private:

};