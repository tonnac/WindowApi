#pragma once
#include "EffectObj.h"


class KahoAttack3 : public EffectObj
{
public:
	bool		Init() override;
	bool		Frame() override;
private:
};