#pragma once
#include "State.h"

class PlayerState : public State
{
public:
	PlayerState(Object*);
public:
	bool		Init		() override;
	bool		Frame		() override;
	bool		Render		() override;
	bool		Release		() override;
private:

};