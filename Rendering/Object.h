#pragma once
#include "BitmapMgr.h"
#include "Input.h"


#define LR_ROTATION    0x01
#define TB_ROTATION    0x02
#define LRTB_ROTATION  0x03

class Rendering;

class Object
{
public:
	Object();
	virtual ~Object() {};
public:
	virtual bool		Init			();
	virtual bool		Frame			();
	virtual bool		Render			();
	virtual bool		Release			();
public:
	RECT&				getrtDraw		();
	FloatPoint&			getDrawPos		();
	HDC					getColorDC		() const;
	HDC					getMaskDC		() const;
	RECT				getCollisionRt	();
	void				DebugMode		();
public:
	bool				LoadFile		(T_STR, T_STR, T_STR = std::basic_string<TCHAR>());
	void				Set				(const FLOAT&, const FLOAT&,
										const DWORD& = 0, const DWORD& = 0, const DWORD& = 0, const DWORD& = 0);
private:
	FloatPoint			m_CenterPos;
	FloatPoint			m_DrawPos;
	FLOAT				m_fSpeed;
	RECT				m_rtDraw;
	RECT				m_rtCollision;
	Bitmap *			m_ColorBitmap;
	Bitmap *			m_MaskBitmap;
	bool				isDebugMode;
	bool				isDead;
	Rendering*			m_pRendering;
};