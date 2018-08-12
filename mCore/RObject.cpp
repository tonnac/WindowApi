#include "RObject.h"

RObject::RObject()
{
	m_fAngle = 0.0f;
	m_fMaxLength = 0.0f;
}

bool RObject::Init()
{
	if (m_fZoom > 1.0f)
	{
		m_fMaxLength = static_cast<float>(m_rtDraw.right) * 2;
	}
	else
	{
		m_fMaxLength = static_cast<float>(sqrt((m_rtDraw.right) * (m_rtDraw.right) + (m_rtDraw.bottom) * (m_rtDraw.bottom)));
	}
	m_hRotationDC = CreateCompatibleDC(g_hOffScreenDC);
	m_hColorDC = CreateCompatibleDC(g_hOffScreenDC);
	m_hMaskDC = CreateCompatibleDC(g_hOffScreenDC);

	m_hbColorBitmap = CreateCompatibleBitmap(g_hScreenDC, static_cast<int>(m_fMaxLength), static_cast<int>(m_fMaxLength));
	m_hbMaskBitmap = CreateCompatibleBitmap(g_hScreenDC, static_cast<int>(m_fMaxLength), static_cast<int>(m_fMaxLength));

	return true;
}
bool RObject::Frame()
{
	m_fAngle += g_fPerSecFrame * 300.0f;

	getRotateBitmap(m_hbColorBitmap, m_ColorBitmap);
	getRotateBitmap(m_hbMaskBitmap, m_MaskBitmap);


	m_DrawPos.x = m_CenterPos.x - (m_rtDraw.right / 2);
	m_DrawPos.y = m_CenterPos.y - (m_rtDraw.bottom / 2);

	FLOAT d = m_rtDraw.right * m_fZoom / 2;
	FLOAT e = m_rtDraw.bottom * m_fZoom / 2;

	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - d);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - e);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + d);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + e);
	return true;
}
bool RObject::Render()
{
	DebugMode();
	HBITMAP oldMask = static_cast<HBITMAP>(SelectObject(m_hMaskDC, m_hbMaskBitmap));
	HBITMAP oldColor = static_cast<HBITMAP>(SelectObject(m_hColorDC, m_hbColorBitmap));

	StretchBlt(g_hOffScreenDC, (m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength), m_CenterPos.y - (m_fMaxLength / 2),
		-static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		m_hMaskDC,
		0,
		0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		SRCAND);
	StretchBlt(g_hOffScreenDC, (m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength), m_CenterPos.y - (m_fMaxLength / 2),
		-static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		m_hColorDC,
		0,
		0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		SRCINVERT);
	StretchBlt(g_hOffScreenDC, (m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength), m_CenterPos.y - (m_fMaxLength / 2),
		-static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		m_hMaskDC,
		0,
		0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		SRCINVERT);
	SelectObject(m_hMaskDC, oldMask);
	SelectObject(m_hColorDC, oldColor);
	if (isDebugMode)
	{
		int iPrev = SetROP2(g_hOffScreenDC, R2_XORPEN);

		//원충돌크기
		//LONG dwX = m_rtCollision.right - m_rtCollision.left;						
		//LONG dwY = m_rtCollision.bottom - m_rtCollision.top;						
		//LONG fRad = (dwX > dwY) ? dwX : dwY;
		//LONG left = m_rtCollision.left - (fRad - m_rtDraw.right) / 2;
		//LONG top = m_rtCollision.top - (fRad - m_rtDraw.bottom) / 2;
		//Ellipse(g_hOffScreenDC, left, top, left + fRad, top + fRad);

		Rectangle(g_hOffScreenDC, m_rtCollision.left, m_rtCollision.top,
			m_rtCollision.right, m_rtCollision.bottom);
		SetROP2(g_hOffScreenDC, iPrev);
	}
	return true;
}
bool RObject::Release()
{
	DeleteDC(m_hRotationDC);
	DeleteDC(m_hColorDC);
	DeleteDC(m_hMaskDC);
	DeleteObject(m_hbColorBitmap);
	DeleteObject(m_hbMaskBitmap);
	return true;
}
void RObject::getRotateBitmap(HBITMAP hbit, Bitmap* pBitmap)
{
	FLOAT fRadian = static_cast<FLOAT>(DegreeToRadian(m_fAngle));
	FLOAT Cosine = cos(fRadian);
	FLOAT Sine = sin(fRadian);

	HBRUSH bkBrush = CreateSolidBrush(RGB(0, 255, 255));

	HBITMAP oldBItmap = static_cast<HBITMAP>(SelectObject(m_hRotationDC, hbit));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hRotationDC, bkBrush));

	PatBlt(m_hRotationDC, 0, 0,
		static_cast<int>(m_fMaxLength), 
		static_cast<int>(m_fMaxLength), PATCOPY);

	DeleteObject(SelectObject(m_hRotationDC, oldBrush));

	int prevGraphic = SetGraphicsMode(m_hRotationDC, GM_ADVANCED);

	XFORM xform;
	xform.eM11 = Cosine;
	xform.eM12 = -Sine;
	xform.eM21 = Sine;
	xform.eM22 = Cosine;
	xform.eDx = m_fMaxLength / 2;
	xform.eDy = m_fMaxLength / 2;

	SetWorldTransform(m_hRotationDC, &xform);

	HDC bitmapDC = pBitmap->getMemDC();
	BitBlt(m_hRotationDC, 
		static_cast<int>(-m_rtDraw.right /2),
		static_cast<int>(-m_rtDraw.bottom / 2),
		m_rtDraw.right, 
		m_rtDraw.bottom, 
		bitmapDC, 
		m_rtDraw.left, m_rtDraw.top, SRCCOPY);

	xform.eM11 = 1;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 = 1;
	xform.eDx = 0;
	xform.eDy = 0;

	SetWorldTransform(m_hRotationDC, &xform);

	SelectObject(m_hRotationDC, oldBItmap);
	SetGraphicsMode(m_hRotationDC, prevGraphic);
}