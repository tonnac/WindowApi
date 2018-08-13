#include "RotateRendering.h"


bool Init()
{
	m_fMaxLength = static_cast<float>(sqrt((m_rtDraw.right) * (m_rtDraw.right) + (m_rtDraw.bottom) * (m_rtDraw.bottom)));

	m_hRotationDC = CreateCompatibleDC(g_hOffScreenDC);
	m_hColorDC = CreateCompatibleDC(g_hOffScreenDC);
	m_hMaskDC = CreateCompatibleDC(g_hOffScreenDC);

	m_hbColorBitmap = CreateCompatibleBitmap(g_hScreenDC, static_cast<int>(m_fMaxLength), static_cast<int>(m_fMaxLength));
	m_hbMaskBitmap = CreateCompatibleBitmap(g_hScreenDC, static_cast<int>(m_fMaxLength), static_cast<int>(m_fMaxLength));
}

void Rendering::getRotateBitmap(HBITMAP hbit, Bitmap* pBitmap)
{
	FLOAT fRadian = static_cast<FLOAT>(DegreeToRadian(m_fAngle));
	FLOAT Cosine = cos(fRadian);
	FLOAT Sine = sin(fRadian);

	HBRUSH bkBrush = CreateSolidBrush(RGB(255, 255, 255));

	HBITMAP oldBItmap = static_cast<HBITMAP>(SelectRendering(m_hRotationDC, hbit));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectRendering(m_hRotationDC, bkBrush));

	PatBlt(m_hRotationDC, 0, 0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength), PATCOPY);

	DeleteRendering(SelectRendering(m_hRotationDC, oldBrush));

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
		static_cast<int>(-m_rtDraw.right / 2),
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

	SelectRendering(m_hRotationDC, oldBItmap);
	SetGraphicsMode(m_hRotationDC, prevGraphic);
}
bool Rendering::RotateRender()
{
	HBITMAP oldMask = static_cast<HBITMAP>(SelectRendering(m_hMaskDC, m_hbMaskBitmap));
	HBITMAP oldColor = static_cast<HBITMAP>(SelectRendering(m_hColorDC, m_hbColorBitmap));

	StretchBlt(g_hOffScreenDC,
		static_cast<int>(m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength),
		static_cast<int>(m_CenterPos.y - (m_fMaxLength / 2)),
		-static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		m_hMaskDC,
		0,
		0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		SRCAND);
	StretchBlt(g_hOffScreenDC,
		static_cast<int>(m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength),
		static_cast<int>(m_CenterPos.y - (m_fMaxLength / 2)),
		-static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		m_hColorDC,
		0,
		0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		SRCINVERT);
	StretchBlt(g_hOffScreenDC,
		static_cast<int>(m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength),
		static_cast<int>(m_CenterPos.y - (m_fMaxLength / 2)),
		-static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		m_hMaskDC,
		0,
		0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		SRCINVERT);
	SelectRendering(m_hMaskDC, oldMask);
	SelectRendering(m_hColorDC, oldColor);
	return true;
}