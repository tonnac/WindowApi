#pragma once
#include "PlayerState.h"


class PlayerAttack2 : public PlayerState
{
public:
	PlayerAttack2(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
	bool		Render() override;
	bool		Release() override;
private:
	FLOAT		m_fTimer;
};