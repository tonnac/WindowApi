#pragma once
#include "Std.h"

struct KPOINT
{
	float x, y;
};

class Bitmap
{
public:
	bool			LoadFile(T_STR szLoadFile);
	T_STR			getName();
	void			SetPosition(float, float);
	void			SetOffset(float, float);
public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
public:
	Bitmap();
	virtual			~Bitmap();
private:
	T_STR			m_szName;
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	BITMAP			m_bmpInfo;
	KPOINT			m_Position;
};