#pragma once
#include "BitmapMgr.h"
#include "Input.h"

class Rendering;


// º“∏Í¿⁄ Delete »Æ¿Œ

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
	RECT&				getCollisionRt	();
	FloatPoint&			getCenterPos	();
	FloatPoint&			getDrawPos		();
	HDC					getColorDC		() const;
	HDC					getMaskDC		() const;
	void				DebugMode		();
public:
	bool				getDebugmode	();
	void				setDebugmode	(const bool&);
public:
	bool				LoadFile		(T_STR, T_STR, T_STR = std::basic_string<TCHAR>());
	void				Set				(const FLOAT&, const FLOAT&,
										const DWORD& = 0, const DWORD& = 0, const DWORD& = 0, const DWORD& = 0);
	void				Set				(const RECT&);
public:
	void				setRendering	(const FLOAT&, const INVERSE&);
	void				setRendering	(const FLOAT&);
	void				setRendering	(const INVERSE&);
public:
	virtual void		MoveScrollBk	(const bool& = false);
	virtual void		MoveScrollObj	(const bool& = false);
public:
	void				setCenterPos_x(const FLOAT&);
protected:
	FLOAT				m_fScroll;
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