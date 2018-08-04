#pragma once
#include "Std.h"

class Bitmap
{
public:
	bool				LoadFile(T_STR);
private:
	T_STR				m_szFileName;
	HBITMAP				m_hBitmap;
	BITMAP				m_bBmpInfo;
};