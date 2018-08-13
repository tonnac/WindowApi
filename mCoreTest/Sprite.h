#pragma once
#include "Object.h"

class Sprite
{
public:
	bool				Init();
	bool				Frame();
//	bool				Render();
	bool				Release();
	bool				AddRect(const RECT&);
	bool				SetDivideTime(const FLOAT&);
public:
	bool				PreFrame();
public:
	INT					m_iIndex;
	FLOAT				m_fDivideTime;
	FLOAT				m_fSpriteTime;
	FLOAT				m_fOffset;
	std::vector<RECT>	m_spritelist;
};