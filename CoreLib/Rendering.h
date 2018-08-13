#include "Std.h"

class Object;

class Rendering
{
public:
	Rendering(const Object&);
	virtual ~Rendering() {};
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();

	void				SetInverse(const SHORT& = 0, const FLOAT& = 1.0f);
	RECT				getCollisionRt();
protected:
	void				getRotateBitmap(HBITMAP, Bitmap*);
	bool				RotateRender();
	bool				NormalRender();
	bool				InversionRender();
private:
	const FloatPoint&	m_DrawPos;
	const RECT&			m_rtDraw;
	const HDC&			m_hColorDC;
	const HDC&			m_hMaskDC;
};