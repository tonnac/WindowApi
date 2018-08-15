#pragma once
#include "Std.h"
#include "Object.h"

class Rendering
{
public:
	Rendering(Object*);
	virtual ~Rendering() {};
public:
	virtual bool		Init	();
	virtual bool		Frame	();
	virtual bool		Render	();
	virtual bool		Release	();
	void * operator new(size_t sz, const char* FileName, int iLine);
	void operator delete(void * p);
protected:
	FloatPoint&			m_CenterPos;
	FloatPoint&			m_DrawPos;
	RECT&				m_rtCollision;
	RECT&				m_rtDraw;
	HDC					m_hColorDC;
	HDC					m_hMaskDC;
};