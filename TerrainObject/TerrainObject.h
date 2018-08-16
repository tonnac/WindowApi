#pragma once
#include "Object.h"

class TerrainObject : public Object
{
public:
	bool				Init			() override;
	bool				Frame			() override;
//	bool				Render			() override;
	bool				Release			() override;
	INT					Collision		(const RECT&);
private:
};