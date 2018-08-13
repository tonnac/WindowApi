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
	void				Set(const FLOAT&, const FLOAT&,
							const DWORD& =0, const DWORD& =0, const DWORD& =0, const DWORD& =0);
	void				SetInverse(const SHORT& = 0, const FLOAT& = 1.0f);
	RECT				getCollisionRt();
public:
	bool				isDead;
	bool				isRotate;
protected:
	void				getRotateBitmap(HBITMAP, Bitmap*);
	bool				RotateRender();
	bool				NormalRender();
	bool				InversionRender();
public:
	FLOAT				m_fSpeed;
	FLOAT				m_fZoom;
	bool				isDebugMode;
	FloatPoint			m_DrawPos;
	FloatPoint			m_CenterPos;
	SHORT				m_sRotation;
	RECT				m_rtDraw;
	RECT				m_rtCollision;
	Bitmap *			m_ColorBitmap;
	Bitmap *			m_MaskBitmap;
protected:
	HDC					m_hRotationDC;
	HDC					m_hColorDC;
	HDC					m_hMaskDC;
	HBITMAP				m_hbColorBitmap;
	HBITMAP				m_hbMaskBitmap;
	FLOAT				m_fAngle;
	FLOAT				m_fMaxLength;
};