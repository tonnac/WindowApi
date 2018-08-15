#pragma once
#include "Object.h"
#include "SpriteMgr.h"

class EffectObj : public Object
{
public:
	virtual bool		Init		();
	virtual bool		Frame		();
	void				setSprite	(Sprite*);
private:
	Sprite *			m_pEffectSprite;
};