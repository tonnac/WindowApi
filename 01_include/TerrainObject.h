#pragma once
#include "Object.h"

class TerrainObject : public Object
{
public:
	bool				Init			() override;
	virtual bool		Frame			() override;
	bool				Render			() override;
	bool				Release			() override;
	virtual	bool		MoveObject		(Object*, const RECT&);
	bool				Collision		(Object*) override;
private:
};