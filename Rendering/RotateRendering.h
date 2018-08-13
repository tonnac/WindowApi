#pragma once
#include "Rendering.h"

class RotateRendering : public Rendering
{
public:
	void				getRotateBitmap(HBITMAP, Bitmap*);
	bool				RotateRender();
private:
	HDC					m_hRotationDC;
	HDC					m_hColorDC;
	HDC					m_hMaskDC;
	HBITMAP				m_hbColorBitmap;
	HBITMAP				m_hbMaskBitmap;
	FLOAT				m_fAngle;
	FLOAT				m_fMaxLength;
};