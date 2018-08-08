#pragma once
#include "BitmapMgr.h"

#define LR_ROTATION 0x01
#define TB_ROTATION 0x02
#define LRTB_ROTATION 0x04

class Object
{
public:
	KPoint					m_CenterPos;
	KPoint					m_DrawPos;
	Bitmap*					m_pColorBitmap;
	Bitmap*					m_pMaskBitmap;
	RECT					m_rtDraw;
	RECT					m_rtCollision;
	float					m_fSpeed;
	float					m_fDir[2];
	bool					isDebugMode;
	bool					isDead;
public:
	virtual void			Set(const KPoint&);
	virtual void			Set(float, float, DWORD, DWORD, DWORD, DWORD);
	virtual bool			LoadFile(const TCHAR*, const TCHAR* = nullptr);
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Render();
	virtual bool			Release();
	virtual bool			Draw(SHORT , RECT* = nullptr);
	virtual bool			DrawColorKey(DWORD);
public:
	Object();
	virtual ~Object();
};