#pragma once
#include "BitmapMgr.h"

#define LR_ROTATION 0x01
#define TB_ROTATION 0x02
#define LRTB_ROTATION 0x04

class Object
{
	KPoint					m_pos;
	Bitmap*					m_pColorBitmap;
	Bitmap*					m_pMaskBitmap;
public:
	RECT					m_rtDraw;
public:
	virtual void			Set(const KPoint&);
	virtual void			Set(float, float, DWORD, DWORD, DWORD, DWORD);
	virtual bool			LoadFile(const TCHAR*, const TCHAR* = 0);
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Render();
	virtual bool			Release();
	virtual bool			Draw(SHORT , RECT* rt = 0);
	virtual bool			DrawColorKey(DWORD);
public:
	Object();
	virtual ~Object();
};