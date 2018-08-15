#pragma once
#include "RotateRendering.h"

class InversionRendering : public Rendering
{
public:
	InversionRendering	(Object*, const FLOAT&, const INVERSE&);
public:
//	bool		Init		() override;
	bool		Frame		() override;
	bool		Render		() override;
//	bool		Release		() override;
	void		setInverse	(const INVERSE&) override;
private:
	INVERSE		m_sInverse;
	FLOAT		m_fZoom;
};