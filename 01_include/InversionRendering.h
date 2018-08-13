#pragma once
#include "Rendering.h"

class InversionRendering : public Rendering
{
public:
	InversionRendering(Object*, const FLOAT& = 0, const SHORT& = 0);
public:
//	bool		Init	() override;
	bool		Frame	() override;
	bool		Render	() override;
//	bool		Release	() override;
private:
	SHORT		m_sInverse;
	FLOAT		m_fZoom;
	FloatPoint&	m_CenterPos;
	FloatPoint&	m_DrawPos;
	RECT&		m_rtCollision;
};