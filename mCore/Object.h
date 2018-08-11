#pragma once
#include "BitmapMgr.h"
#include "Input.h"

#define LR_ROTATION    0x01
#define TB_ROTATION    0x02
#define LRTB_ROTATION  0x03

class Object
{
public:
	Object();
	virtual ~Object() {};
public:
	bool				DebugMode();
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	bool				LoadFile(T_STR, T_STR, T_STR = std::basic_string<TCHAR>());
	void				Set(const float&, const float&,
							const DWORD&, const DWORD&, const DWORD&, const DWORD&);
	void				SetInverse(SHORT, RECT* = nullptr);
	RECT				getCollisionRt();
public:
	bool				isDead;
protected:
	bool				NormalRender();
	bool				InversionRender();
protected:
	float				m_fSpeed;
	bool				isDebugMode;
	FloatPoint			m_DrawPos;
	FloatPoint			m_CenterPos;
	RECT*				m_rtZoom;
	SHORT				m_sRotation;
	RECT				m_rtDraw;
	RECT				m_rtCollision;
	Bitmap *			m_ColorBitmap;
	Bitmap *			m_MaskBitmap;
};