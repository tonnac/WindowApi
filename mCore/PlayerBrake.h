#pragma once
#include "PlayerState.h"

class PlayerBrake : public PlayerState
{
public:
	PlayerBrake(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
	bool		Release() override;
private:

};