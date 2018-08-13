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
protected:
	FloatPoint&			m_DrawPos;
	RECT&				m_rtDraw;
	HDC					m_hColorDC;
	HDC					m_hMaskDC;
};