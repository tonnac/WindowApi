#pragma once
#include "SpriteMgr.h"
#include "Player.h"

class State
{
public:
	State(Object*);
public:
	virtual bool		Init		() = 0;
	virtual bool		Frame		() = 0;
	virtual bool		Render		() = 0;
	virtual bool		Release		() = 0;
public:
	void				setSprite	(T_STR, T_STR);
public:
	void * operator new(size_t sz, const char* FileName, int iLine);
	void operator delete(void * p);
protected:
	Object *			m_pObject;
	Sprite *			m_pSprite;
	FloatPoint&			m_CenterPos;
	FloatPoint&			m_DrawPos;
	RECT&				m_rtCollision;
	RECT&				m_rtDraw;
};

