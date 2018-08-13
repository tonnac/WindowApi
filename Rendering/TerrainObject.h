#pragma once
#include "Object.h"
#include "Player.h"
class TerrainObject : public Object
{
public:
	TerrainObject(Player*);
protected:
	Player * _Player;
};