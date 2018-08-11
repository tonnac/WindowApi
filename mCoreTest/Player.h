#pragma once
#include "Object.h"

class Player : public Object
{
public:
	bool		Init() override;
	bool		Frame() override;
private:

};