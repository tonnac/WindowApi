#pragma once
#include "Rendering.h"

#define LR_ROTATION    0x01
#define TB_ROTATION    0x02
#define LRTB_ROTATION  0x03

class InversionRendering : public Rendering
{
public:
	InversionRendering(Object*, const SHORT& = 0, const FLOAT& = 0);
public:
//	bool		Init	() override;
	bool		Frame	() override;
	bool		Render	() override;
//	bool		Release	() override;
private:
	SHORT		m_sInverse;
	FLOAT		m_fZoom;
};