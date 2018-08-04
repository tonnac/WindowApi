#pragma once
#include "Std.h"

class Bitmap
{
public:
	bool				LoadFile(T_STR);
	bool				Init();
	bool				Frame();
	bool				Render();
	bool				Release();
private:
	T_STR				m_szFileName;
	HBITMAP				m_hBitmap;
	HBITMAP				m_hofbit;
	BITMAP				m_bBmpInfo;
public:
	HDC					m_hMemDC;
private:
	HBRUSH				m_hBkColor;
};