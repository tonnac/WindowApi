#pragma once
#include "PlayerState.h"

class PlayerAttack : public PlayerState
{
public:
	PlayerAttack(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
	bool		Release() override;
private:

};