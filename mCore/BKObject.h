#pragma once
#include "Object.h"

class TerrainObject;

class BKObject : public Object
{
public:
//	bool		Init			() override;
	bool		Frame			() override;
	bool		Render			() override;
	bool		MoveScrollBk	(const LONG&) override;
	void		AddTerrain		(TerrainObject *);
	bool		Collision		(Object* ) override;
private:
	std::vector<TerrainObject*> m_pObjList;
};