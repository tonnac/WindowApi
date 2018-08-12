#include "Object.h"

Object::Object()
{
	m_ColorBitmap = nullptr;
	m_MaskBitmap = nullptr;
	isDebugMode = true;
	isDead = false;
	isRotate = false;
	m_sRotation = -1;
	m_fZoom = 1.0f;
	m_fAngle = 0.0f;
	m_fMaxLength = 0.0f;
	m_hRotationDC = nullptr;
	m_hColorDC = nullptr;
	m_hMaskDC = nullptr;
	m_hbColorBitmap = nullptr;
	m_hbMaskBitmap = nullptr;
}
bool Object::DebugMode()
{
	if (S_Input.GetKey(VK_HOME) == KEYSTATE::KEY_PUSH)
	{
		isDebugMode = !isDebugMode;
	}
	return true;
}
bool Object::Init()
{
	m_fMaxLength = static_cast<float>(sqrt((m_rtDraw.right) * (m_rtDraw.right) + (m_rtDraw.bottom) * (m_rtDraw.bottom)));

	m_hRotationDC = CreateCompatibleDC(g_hOffScreenDC);
	m_hColorDC = CreateCompatibleDC(g_hOffScreenDC);
	m_hMaskDC = CreateCompatibleDC(g_hOffScreenDC);

	m_hbColorBitmap = CreateCompatibleBitmap(g_hScreenDC, static_cast<int>(m_fMaxLength), static_cast<int>(m_fMaxLength));
	m_hbMaskBitmap = CreateCompatibleBitmap(g_hScreenDC, static_cast<int>(m_fMaxLength), static_cast<int>(m_fMaxLength));

	return true;
}
bool Object::Frame()
{
	m_fAngle += g_fPerSecFrame * 300.0f;


	m_DrawPos.x = m_CenterPos.x - (m_rtDraw.right * m_fZoom / 2);
	m_DrawPos.y = m_CenterPos.y - (m_rtDraw.bottom * m_fZoom / 2);

	FLOAT d = m_rtDraw.right * m_fZoom / 2;
	FLOAT e = m_rtDraw.bottom * m_fZoom / 2;

	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - d);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - e);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + d);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + e);

	if (isRotate)
	{
		getRotateBitmap(m_hbColorBitmap, m_ColorBitmap);
		getRotateBitmap(m_hbMaskBitmap, m_MaskBitmap);
	}
	return true;
}
bool Object::Render()
{
	DebugMode();
	if (m_fZoom > 1.0f || m_sRotation > 0)
	{
		InversionRender();
	}
	else if (isRotate)
	{
		RotateRender();
	}
	else
		NormalRender();

	if (isDebugMode)
	{
		int iPrev = SetROP2(g_hOffScreenDC, R2_MASKPEN);

		//원충돌크기
		//LONG dwX = m_rtCollision.right - m_rtCollision.left;						
		//LONG dwY = m_rtCollision.bottom - m_rtCollision.top;						
		//LONG fRad = (dwX > dwY) ? dwX : dwY;
		//LONG left = m_rtCollision.left - (fRad - m_rtDraw.right) / 2;
		//LONG top = m_rtCollision.top - (fRad - m_rtDraw.bottom) / 2;
		//Ellipse(g_hOffScreenDC, left, top, left + fRad, top + fRad);

		Rectangle(g_hOffScreenDC, m_rtCollision.left, m_rtCollision.top,
			m_rtCollision.right, m_rtCollision.bottom);

		SetROP2(g_hOffScreenDC, iPrev);
	}
	return true;
}
bool Object::Release()
{
	DeleteDC(m_hRotationDC);
	DeleteDC(m_hColorDC);
	DeleteDC(m_hMaskDC);
	DeleteObject(m_hbColorBitmap);
	DeleteObject(m_hbMaskBitmap);
	return true;
}
bool Object::LoadFile(T_STR szName, T_STR szColorFile, T_STR szMaskFile)
{
	T_STR bitmapName;
	if (!szMaskFile.empty())
	{
		T_STR maskname = szName + L"Mask";
		bitmapName = S_BitmapMgr.LoadFile(maskname, szMaskFile);
		m_MaskBitmap = S_BitmapMgr.getBitmapPtr(bitmapName);
	}
	bitmapName = S_BitmapMgr.LoadFile(szName, szColorFile);
	m_ColorBitmap = S_BitmapMgr.getBitmapPtr(bitmapName);
	return true;
}
void Object::Set(const FLOAT& x, const FLOAT& y,
	const DWORD& l, const DWORD& t, const DWORD& r, const DWORD& b)
{
	m_CenterPos.x = x;
	m_CenterPos.y = y;

	m_rtDraw.left = l;
	m_rtDraw.top = t;
	m_rtDraw.bottom = b;
	m_rtDraw.right = r;

	m_DrawPos.x = m_CenterPos.x - (m_rtDraw.right * m_fZoom / 2);
	m_DrawPos.y = m_CenterPos.y - (m_rtDraw.bottom * m_fZoom / 2);

	FLOAT d = m_rtDraw.right * m_fZoom / 2;
	FLOAT e = m_rtDraw.bottom * m_fZoom / 2;

	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - d);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - e);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + d);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + e);

}
void Object::SetInverse(const SHORT& Key, const FLOAT& fZoom)
{
	m_sRotation = Key;
	m_fZoom = fZoom;
}
RECT Object::getCollisionRt()
{
	return m_rtCollision;
}
void Object::getRotateBitmap(HBITMAP hbit, Bitmap* pBitmap)
{
	FLOAT fRadian = static_cast<FLOAT>(DegreeToRadian(m_fAngle));
	FLOAT Cosine = cos(fRadian);
	FLOAT Sine = sin(fRadian);

	HBRUSH bkBrush = CreateSolidBrush(RGB(255, 255, 255));

	HBITMAP oldBItmap = static_cast<HBITMAP>(SelectObject(m_hRotationDC, hbit));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hRotationDC, bkBrush));

	PatBlt(m_hRotationDC, 0, 0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength), PATCOPY);

	DeleteObject(SelectObject(m_hRotationDC, oldBrush));

	int prevGraphic = SetGraphicsMode(m_hRotationDC, GM_ADVANCED);

	XFORM xform;
	xform.eM11 = Cosine;
	xform.eM12 = -Sine;
	xform.eM21 = Sine;
	xform.eM22 = Cosine;
	xform.eDx = m_fMaxLength / 2;
	xform.eDy = m_fMaxLength / 2;

	SetWorldTransform(m_hRotationDC, &xform);

	HDC bitmapDC = pBitmap->getMemDC();
	BitBlt(m_hRotationDC,
		static_cast<int>(-m_rtDraw.right / 2),
		static_cast<int>(-m_rtDraw.bottom / 2),
		m_rtDraw.right,
		m_rtDraw.bottom,
		bitmapDC,
		m_rtDraw.left, m_rtDraw.top, SRCCOPY);

	xform.eM11 = 1;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 = 1;
	xform.eDx = 0;
	xform.eDy = 0;

	SetWorldTransform(m_hRotationDC, &xform);

	SelectObject(m_hRotationDC, oldBItmap);
	SetGraphicsMode(m_hRotationDC, prevGraphic);
}
bool Object::RotateRender()
{
	HBITMAP oldMask = static_cast<HBITMAP>(SelectObject(m_hMaskDC, m_hbMaskBitmap));
	HBITMAP oldColor = static_cast<HBITMAP>(SelectObject(m_hColorDC, m_hbColorBitmap));

	StretchBlt(g_hOffScreenDC, 
		static_cast<int>(m_CenterPos.x - (m_fMaxLength / 2) +m_fMaxLength),
		static_cast<int>(m_CenterPos.y - (m_fMaxLength / 2)),
		-static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		m_hMaskDC,
		0,
		0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		SRCAND);
	StretchBlt(g_hOffScreenDC, 
		static_cast<int>(m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength),
		static_cast<int>(m_CenterPos.y - (m_fMaxLength / 2)),
		-static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		m_hColorDC,
		0,
		0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		SRCINVERT);
	StretchBlt(g_hOffScreenDC,
		static_cast<int>(m_CenterPos.x - (m_fMaxLength / 2) + m_fMaxLength),
		static_cast<int>(m_CenterPos.y - (m_fMaxLength / 2)),
		-static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		m_hMaskDC,
		0,
		0,
		static_cast<int>(m_fMaxLength),
		static_cast<int>(m_fMaxLength),
		SRCINVERT);
	SelectObject(m_hMaskDC, oldMask);
	SelectObject(m_hColorDC, oldColor);
	return true;
}
bool Object::NormalRender()
{
	HDC ColorDC = m_ColorBitmap->getMemDC();
	if (m_MaskBitmap == nullptr)
	{
		BitBlt(g_hOffScreenDC, 
			static_cast<int>(m_DrawPos.x),
			static_cast<int>(m_DrawPos.y),
			m_rtDraw.right,
			m_rtDraw.bottom,
			ColorDC,
			m_rtDraw.left,
			m_rtDraw.top,
			SRCCOPY);
		return true;
	}
	HDC MaskDC = m_MaskBitmap->getMemDC();
	BitBlt(g_hOffScreenDC, 
		static_cast<int>(m_DrawPos.x),
		static_cast<int>(m_DrawPos.y),
		m_rtDraw.right,
		m_rtDraw.bottom,
		MaskDC,
		m_rtDraw.left,
		m_rtDraw.top, SRCAND);
	BitBlt(g_hOffScreenDC, 
		static_cast<int>(m_DrawPos.x),
		static_cast<int>(m_DrawPos.y),
		m_rtDraw.right,
		m_rtDraw.bottom,
		ColorDC,
		m_rtDraw.left,
		m_rtDraw.top,
		SRCINVERT);
	BitBlt(g_hOffScreenDC, 
		static_cast<int>(m_DrawPos.x),
		static_cast<int>(m_DrawPos.y),
		m_rtDraw.right,
		m_rtDraw.bottom,
		MaskDC,
		m_rtDraw.left,
		m_rtDraw.top,
		SRCINVERT);
	return true;
}
bool Object::InversionRender()
{
	HDC ColorDC = m_ColorBitmap->getMemDC();
	if (m_MaskBitmap == nullptr)
	{
		switch (m_sRotation)
		{
		case LR_ROTATION:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(-m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCCOPY);
			break;
		case TB_ROTATION:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				static_cast<int>(m_rtDraw.right),
				static_cast<int>(-m_rtDraw.bottom),
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCCOPY);
			break;
		case LRTB_ROTATION:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				static_cast<int>(-m_rtDraw.right),
				static_cast<int>(-m_rtDraw.bottom),
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCCOPY);
			break;
		default:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCCOPY);
		}
	}
	else
	{
		HDC MaskDC = m_MaskBitmap->getMemDC();
		switch (m_sRotation)
		{
		case LR_ROTATION:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right * m_fZoom),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(-m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right * m_fZoom),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(-m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right * m_fZoom),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(-m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			break;
		case TB_ROTATION:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				m_rtDraw.right, 
				-m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				m_rtDraw.right, -m_rtDraw.bottom,
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				m_rtDraw.right, -m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			break;
		case LRTB_ROTATION:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				-m_rtDraw.right, -m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				-m_rtDraw.right, -m_rtDraw.bottom,
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right), 
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				-m_rtDraw.right, -m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			break;
		default:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
		}
	}
	return true;
}