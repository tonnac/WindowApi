#pragma once
#include "CharacterObject.h"

class NPC : public CharacterObject
{
public:
	NPC();
	~NPC();
public:
	bool		Frame() override;
private:
};