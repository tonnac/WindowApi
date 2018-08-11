#include "RotationObject.h"

bool RotationObject::Init()
{
	m_bkBrush = CreateSolidBrush(RGB(0, 0, 255));
	m_bColor.Init();
	m_bMask.Init();
	m_bColor.Set(500, 500, 133, 1, 42, 59);
	m_bMask.Set(500, 500, 133, 1, 42, 59);
	m_bColor.LoadFile(L"../02_data/bitmap1.bmp");
	m_bMask.LoadFile(L"../02_data/bitmap2.bmp");
	m_fDiff = sqrt((m_bColor.m_rtDraw.right) * (m_bColor.m_rtDraw.right) +
		(m_bColor.m_rtDraw.bottom) * (m_bColor.m_rtDraw.bottom));
	m_fAngle = 0.0f;
	m_RotationDC = CreateCompatibleDC(g_hScreenDC);
	m_hColorDC = CreateCompatibleDC(g_hScreenDC);
	m_hMaskDC = CreateCompatibleDC(g_hScreenDC);


	m_hColorBitmap = CreateCompatibleBitmap(g_hScreenDC, m_fDiff, m_fDiff);
	m_hMaskBitmap = CreateCompatibleBitmap(g_hScreenDC, m_fDiff, m_fDiff);

	return true;
}
void RotationObject::Rotate(HBITMAP bitmap, Bitmap pk)
{
	float fRad = DegreetoRadian(m_fAngle);
	float fCosine = cos(fRad);
	float fSine = sin(fRad);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(m_RotationDC, m_bkBrush);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_RotationDC, bitmap);

	PatBlt(m_RotationDC, 0, 0, m_fDiff, m_fDiff, PATCOPY);
//	SelectObject(m_RotationDC, hOldBrush);

	int OldGraphic = SetGraphicsMode(m_RotationDC, GM_ADVANCED);

	XFORM xform1;
	xform1.eM11 = fCosine;		xform1.eM12 = fSine;
	xform1.eM21 = -fSine;		xform1.eM22 = fCosine;
	xform1.eDx = m_fDiff / 2;	xform1.eDy = m_fDiff / 2;

	SetWorldTransform(m_RotationDC, &xform1);

	BitBlt(m_RotationDC, -(m_bColor.m_rtDraw.right / 2), -(m_bColor.m_rtDraw.bottom / 2),
		m_bColor.m_rtDraw.right, m_bColor.m_rtDraw.bottom, pk.m_hMemDC,
		m_bColor.m_rtDraw.left, m_bColor.m_rtDraw.top, SRCCOPY);

	SelectObject(m_RotationDC, hOldBrush);
	SelectObject(m_RotationDC, hOldBitmap);

	xform1.eM11 = 1;		xform1.eM12 = 0;
	xform1.eM21 = 0;		xform1.eM22 = 1;
	xform1.eDx = 0;	xform1.eDy = 0;
	SetWorldTransform(m_RotationDC, &xform1);
	SetGraphicsMode(m_RotationDC, OldGraphic);
}
bool RotationObject::Frame()
{
	m_fAngle += 0.3f;
	Rotate(m_hMaskBitmap, m_bMask);
	Rotate(m_hColorBitmap, m_bColor);

	return true;
}
bool RotationObject::Render()
{
	HBITMAP hOldMask = (HBITMAP)SelectObject(m_hMaskDC, m_hMaskBitmap);
	HBITMAP hOldColor = (HBITMAP)SelectObject(m_hColorDC, m_hColorBitmap);

	BitBlt(g_hOffScreenDC,
		m_bColor.m_CenterPos.x - (m_fDiff / 2),
		m_bColor.m_CenterPos.y - (m_fDiff / 2),
		m_fDiff,
		m_fDiff,
		m_hMaskDC,
		0, 0,
		SRCAND);
	BitBlt(g_hOffScreenDC,
		m_bColor.m_CenterPos.x - (m_fDiff / 2),
		m_bColor.m_CenterPos.y - (m_fDiff / 2),
		m_fDiff,
		m_fDiff,
		m_hColorDC,
		0, 0,
		SRCINVERT);
	BitBlt(g_hOffScreenDC,
		m_bColor.m_CenterPos.x - (m_fDiff / 2),
		m_bColor.m_CenterPos.y - (m_fDiff / 2),
		m_fDiff,
		m_fDiff,
		m_hMaskDC,
		0, 0,
		SRCINVERT);

	SelectObject(m_hMaskDC, hOldMask);
	SelectObject(m_hColorDC, hOldColor);

	return true;
}
bool RotationObject::Release()
{
	DeleteDC(m_hColorDC);
	DeleteDC(m_hMaskDC);
	DeleteDC(m_RotationDC);
	DeleteObject(m_hColorBitmap);
	DeleteObject(m_hMaskBitmap);
	return true;
}
