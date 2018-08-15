#pragma once
#include "PlayerState.h"

class PlayerRunState : public PlayerState
{
public:
	PlayerRunState(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
	bool		Release() override;
private:

};