#pragma once
#include "EffectObj.h"


class KahoAttack2 : public EffectObj
{
public:
	bool		Init() override;
	bool		Frame() override;
private:
};