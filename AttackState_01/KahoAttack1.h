#pragma once
#include "EffectObj.h"


class KahoAttack1 : public EffectObj
{
public:
	bool		Init() override;
	bool		Frame() override;
private:
};