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
	void				SetDegree(FLOAT);
private:
	void				getRotateBitmap(HBITMAP, Bitmap*);
	void				getRotateBitmap(HBITMAP, Bitmap*, float);
private:
	bool				isFixed;
	HDC					m_hRotationDC;
	HDC					m_hColorDC;
	HDC					m_hMaskDC;
	HBITMAP				m_hbColorBitmap;
	HBITMAP				m_hbMaskBitmap;
	FLOAT				m_fAngle;
	FLOAT				m_fMaxLength;
};