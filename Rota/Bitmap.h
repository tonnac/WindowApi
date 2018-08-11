#pragma once
#include "Core.h"

class Bitmap
{
public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
	bool			LoadFile(const TCHAR*);
	void			Set(float, float, LONG, LONG, LONG, LONG);
public:
	RECT			m_rtDraw;
	POINT			m_CenterPos;
	POINT			m_DrasPos;
	HBITMAP			m_hBitmap;
	HDC				m_hMemDC;
};