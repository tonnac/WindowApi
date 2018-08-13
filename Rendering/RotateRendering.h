#pragma once
#include "Rendering.h"

class RotateRendering : public Rendering
{
public:
	void				getRotateBitmap	(HBITMAP, Bitmap*);
	bool				RotateRender	();
public:
	bool				Init			() override;
	bool				Frame			() override;
	bool				Render			() override;
	bool				Release			() override;
private:
	SHORT				m_sInverse;
	FLOAT				m_fZoom;

	HDC					m_hRotationDC;
	HDC					m_hColorDC;
	HDC					m_hMaskDC;
	HBITMAP				m_hbColorBitmap;
	HBITMAP				m_hbMaskBitmap;
	FLOAT				m_fAngle;
	FLOAT				m_fMaxLength;
};