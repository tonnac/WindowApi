#pragma once
#include "Std.h"

struct KPOINT
{
	float x, y;
};

class Bitmap
{
public:
	Bitmap();
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
public:
	BITMAP				m_bBmpInfo;
	HDC					m_hMemDC;
	KPOINT				m_kPos;
private:
	HBRUSH				m_hBkColor;
};