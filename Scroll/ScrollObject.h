#pragma once
#include "Object.h"

class ScrollObject
{
public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
	bool			Set(const RECT&);
	INT				Collision(const RECT&);
private:
	FloatPoint			m_CenterPos[2];
	FloatPoint			m_DrawPos[2];
	RECT				m_rtDraw[2];
	RECT				m_rtCollision[2];
};