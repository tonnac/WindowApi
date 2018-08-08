#pragma once
#include "Object.h"

class NPCObj : public Object
{
public:
	bool				Frame() override;
	NPCObj();
private:
};