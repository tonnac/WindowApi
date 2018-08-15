#pragma once
#include "PlayerState.h"

class PlayerRun : public PlayerState
{
public:
	PlayerRun(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
	bool		Release() override;
private:

};