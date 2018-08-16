#pragma once
#include "State.h"
#include "Player.h"

class EffectObj;

class PlayerState : public State
{
public:
	PlayerState(Player*);
public:
	virtual bool		Init		() override;
	virtual bool		Frame		() override;
	virtual bool		Render		() override;
	virtual bool		Release		() override;
protected:
	EffectObj *			m_pEffectObj;
};