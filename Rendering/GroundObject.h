#pragma once
#include "TerrainObject.h"

class GroundObject : public TerrainObject
{
public:
	GroundObject(Player *);
public:
	bool			Frame();
//	bool			Render();
};