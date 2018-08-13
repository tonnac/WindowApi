#include "RotateRendering.h"

RotateRendering::RotateRendering(Object*ob, const FLOAT& angle) : Rendering(ob), m_fAngle(angle), m_fMaxLength(0.0f)
{}
bool RotateRendering::Init()
{
	m_fMaxLength = static_cast<float>(sqrt((m_rtDraw.right) * (m_rtDraw.right) + (m_rtDraw.bottom) * (m_rtDraw.bottom)));

	m_hRotationDC = CreateCompatibleDC(g_hOffScreenDC);
	m_hColorDC = CreateCompatibleDC(g_hOffScreenDC);
	m_hMaskDC = CreateCompatibleDC(g_hOffScreenDC);

	m_hbColorBitmap = CreateCompatibleBitmap(g_hScreenDC, static_cast<int>(m_fMaxLength), static_cast<int>(m_fMaxLength));
	m_hbMaskBitmap = CreateCompatibleBitmap(g_hScreenDC, static_cast<int>(m_fMaxLength), static_cast<int>(m_fMaxLength));
}
bool RotateRendering::Frame()
{
	getRotateBitmap(m_hbMaskBitmap, m_hMaskDC);
	getRotateBitmap(m_hbColorBitmap, m_hColorDC);
	return true;
}
bool RotateRendering::Render()
{
	HBITMAP oldMask = static_cast<HBITMAP>(SelectObject(m_hMaskDC, m_hbMaskBitmap));
	HBITMAP oldColor = static_cast<HBITMAP>(SelectObject(m_hColorDC, m_hbColorBitmap));

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
	SelectObject(m_hMaskDC, oldMask);
	SelectObject(m_hColorDC, oldColor);
	return true;
}

bool RotateRendering::Release()
{
	DeleteDC(m_hRotationDC);
	DeleteDC(m_hColorDC);
	DeleteDC(m_hMaskDC);
	DeleteObject(m_hbColorBitmap);
	DeleteObject(m_hbMaskBitmap);
}
void RotateRendering::getRotateBitmap(HBITMAP hbit, HDC MemDC)
{
	FLOAT fRadian = static_cast<FLOAT>(DegreeToRadian(m_fAngle));
	FLOAT Cosine = cos(fRadian);
	FLOAT Sine = sin(fRadian);

	HBRUSH bkBrush = CreateSolidBrush(RGB(255, 255, 255));

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

	BitBlt(m_hRotationDC,
		static_cast<int>(-m_rtDraw.right / 2),
		static_cast<int>(-m_rtDraw.bottom / 2),
		m_rtDraw.right,
		m_rtDraw.bottom,
		MemDC,
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