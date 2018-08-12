#include "BKObject.h"

bool BKObject::Frame()
{
	return true;
}

bool BKObject::Render()
{
	HDC ColorDC = m_ColorBitmap->getMemDC();
	StretchBlt(g_hOffScreenDC,
		0,
		0,
		g_rtClient.right, g_rtClient.bottom,
		ColorDC,
		m_rtDraw.left, m_rtDraw.top,
		m_rtDraw.right, m_rtDraw.bottom,
		SRCCOPY);
	return true;
}