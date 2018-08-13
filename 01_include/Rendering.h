#pragma once
#include "Std.h"
#include "Object.h"

class Rendering
{
public:
	Rendering(Object*);
	virtual ~Rendering() {};
public:
	virtual bool		Init	();
	virtual bool		Frame	();
	virtual bool		Render	();
	virtual bool		Release	();
	void * operator new(size_t sz, const char* FileName, int iLine);
	void operator delete(void * p);
protected:
	FloatPoint&			m_CenterPos;
	FloatPoint&			m_DrawPos;
	RECT&				m_rtCollision;
	RECT&				m_rtDraw;
	HDC					m_hColorDC;
	HDC					m_hMaskDC;
};

//
//void Object::getRotateBitmap(HBITMAP hbit, Bitmap* pBitmap)
//{
//	FLOAT fRadian = static_cast<FLOAT>(DegreeToRadian(m_fAngle));
//	FLOAT Cosine = cos(fRadian);
//	FLOAT Sine = sin(fRadian);
//
//	HBRUSH bkBrush = CreateSolidBrush(RGB(255, 255, 255));
//
//	HBITMAP oldBItmap = static_cast<HBITMAP>(SelectObject(m_hRotationDC, hbit));
//	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hRotationDC, bkBrush));
//
//	PatBlt(m_hRotationDC, 0, 0,
//		static_cast<int>(m_fMaxLength),
//		static_cast<int>(m_fMaxLength), PATCOPY);
//
//	DeleteObject(SelectObject(m_hRotationDC, oldBrush));
//
//	int prevGraphic = SetGraphicsMode(m_hRotationDC, GM_ADVANCED);
//
//	XFORM xform;
//	xform.eM11 = Cosine;
//	xform.eM12 = -Sine;
//	xform.eM21 = Sine;
//	xform.eM22 = Cosine;
//	xform.eDx = m_fMaxLength / 2;
//	xform.eDy = m_fMaxLength / 2;
//
//	SetWorldTransform(m_hRotationDC, &xform);
//
//	HDC bitmapDC = pBitmap->getMemDC();
//	BitBlt(m_hRotationDC,
//		static_cast<int>(-m_rtDraw.right / 2),
//		static_cast<int>(-m_rtDraw.bottom / 2),
//		m_rtDraw.right,
//		m_rtDraw.bottom,
//		bitmapDC,
//		m_rtDraw.left, m_rtDraw.top, SRCCOPY);
//
//	xform.eM11 = 1;
//	xform.eM12 = 0;
//	xform.eM21 = 0;
//	xform.eM22 = 1;
//	xform.eDx = 0;
//	xform.eDy = 0;
//
//	SetWorldTransform(m_hRotationDC, &xform);
//
//	SelectObject(m_hRotationDC, oldBItmap);
//	SetGraphicsMode(m_hRotationDC, prevGraphic);
//}
//bool Object::RotateRender()
//{
//	HBITMAP oldMask = static_cast<HBITMAP>(SelectObject(m_hMaskDC, m_hbMaskBitmap));
//	HBITMAP oldColor = static_cast<HBITMAP>(SelectObject(m_hColorDC, m_hbColorBitmap));
//
//	StretchBlt(g_hOffScreenDC,
//		static_cast<int>(m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength),
//		static_cast<int>(m_CenterPos.y - (m_fMaxLength / 2)),
//		-static_cast<int>(m_fMaxLength),
//		static_cast<int>(m_fMaxLength),
//		m_hMaskDC,
//		0,
//		0,
//		static_cast<int>(m_fMaxLength),
//		static_cast<int>(m_fMaxLength),
//		SRCAND);
//	StretchBlt(g_hOffScreenDC,
//		static_cast<int>(m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength),
//		static_cast<int>(m_CenterPos.y - (m_fMaxLength / 2)),
//		-static_cast<int>(m_fMaxLength),
//		static_cast<int>(m_fMaxLength),
//		m_hColorDC,
//		0,
//		0,
//		static_cast<int>(m_fMaxLength),
//		static_cast<int>(m_fMaxLength),
//		SRCINVERT);
//	StretchBlt(g_hOffScreenDC,
//		static_cast<int>(m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength),
//		static_cast<int>(m_CenterPos.y - (m_fMaxLength / 2)),
//		-static_cast<int>(m_fMaxLength),
//		static_cast<int>(m_fMaxLength),
//		m_hMaskDC,
//		0,
//		0,
//		static_cast<int>(m_fMaxLength),
//		static_cast<int>(m_fMaxLength),
//		SRCINVERT);
//	SelectObject(m_hMaskDC, oldMask);
//	SelectObject(m_hColorDC, oldColor);
//	return true;
//}
