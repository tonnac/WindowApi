#include "Bitmap.h"

#define PI 3.141592
#define DegreetoRadian(x) (x) * PI / 180.0f

class RotationObject
{
public:
	bool				Init();
	bool				Frame();
	bool				Render();
	bool				Release();
	void				Rotate(HBITMAP bitmap, Bitmap pk);
public:
	Bitmap				m_bColor;
	Bitmap				m_bMask;
	HBRUSH				m_bkBrush;
	float				m_fAngle;
	float				m_fDiff;
	HDC					m_hColorDC;
	HDC					m_hMaskDC;
	HDC					m_RotationDC;
	HBITMAP				m_hColorBitmap;
	HBITMAP				m_hMaskBitmap;
};