#pragma once
#include "Object.h"

class Sprite : public Object
{
public:
	bool				Init() override;
	bool				Frame() override;
//	bool				Render() override;
	bool				Release() override;
	bool				AddRect(const RECT&);
	bool				SetRect(const RECT&);
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