#pragma once
#include "PlayerState.h"


class PlayerAttack3 : public PlayerState
{
public:
	PlayerAttack3(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
	bool		Release() override;
private:
	FLOAT		m_fTimer;
};