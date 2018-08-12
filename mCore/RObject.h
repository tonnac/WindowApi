#pragma once
#include "Object.h"

class RObject : public Object
{
public:
	RObject();
public:
	bool				Init() override;
	bool				Frame() override;
	bool				Render() override;
	bool				Release() override;
public:
private:
	void				getRotateBitmap(HBITMAP, Bitmap*);
private:
	HDC					m_hRotationDC;
	HDC					m_hColorDC;
	HDC					m_hMaskDC;
	HBITMAP				m_hbColorBitmap;
	HBITMAP				m_hbMaskBitmap;
	FLOAT				m_fAngle;
	FLOAT				m_fMaxLength;
};