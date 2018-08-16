#pragma once
#include "State.h"
#include "Player.h"

class EffectObj;

class PlayerState : public State
{
public:
	PlayerState(Player*);
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
protected:
	EffectObj * m_pEffectObj;
};

class PlayerRun : public PlayerState
{
public:
	PlayerRun(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
private:
};

class PlayerBrake : public PlayerState
{
public:
	PlayerBrake(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
private:
};

class PlayerTurn : public PlayerState
{
public:
	PlayerTurn(Player*);
public:
	bool		Init() override;
	bool		Frame() override;
private:
};