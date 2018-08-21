#pragma once
#include "Object.h"

class Scroll
{
public:
	Scroll(Object * object, Object * pBkObj);
public:
	bool				Init		();
	bool				Frame		();
	bool				Render		();
	bool				Release		();
	bool				Set			(const RECT&);
	void				MoveCamera	(SCROLL);
private:
	SCROLL				Collision	(const RECT&);
private:
	Object*				m_pPlayer;
	Object*				m_pBkObj;
	RECT&				m_PlayerCollisionRt;
	RECT&				m_BkRtDraw;
	FloatPoint			m_CenterPos[2];
	RECT				m_rtCollision[2];
};