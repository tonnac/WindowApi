#pragma once
#include "PlayerState.h"

class PlayerBrakeState : public PlayerState
{
public:
	PlayerBrakeState(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
	bool		Release() override;
private:

};