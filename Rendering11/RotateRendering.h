#pragma once
#include "Rendering.h"

class RotateRendering : public Rendering
{
public:
	RotateRendering(Object*, const FLOAT&);
public:
	void				getRotateBitmap	(HBITMAP, HDC);
public:
	bool				Init			() override;
	bool				Frame			() override;
	bool				Render			() override;
	bool				Release			() override;
private:
	HDC					m_hRotationDC;
	HDC					m_hRColorDC;
	HDC					m_hRMaskDC;
	HBITMAP				m_hbColorBitmap;
	HBITMAP				m_hbMaskBitmap;

	FLOAT				m_fAngle;
	FLOAT				m_fMaxLength;
};