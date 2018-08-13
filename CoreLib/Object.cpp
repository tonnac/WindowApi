#include "Object.h"

Object::Object() : m_Rendering(*this), m_ColorBitmap(nullptr), m_MaskBitmap(nullptr), isDebugMode(false),
					isDead(false), m_fSpeed(0.0f)
{}
bool Object::Init()
{
	
	return true;
}
bool Object::Frame()
{
	m_DrawPos.x = m_CenterPos.x - (m_rtDraw.right / 2);
	m_DrawPos.y = m_CenterPos.y - (m_rtDraw.bottom / 2);


	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - m_rtDraw.right / 2);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - m_rtDraw.bottom / 2);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + m_rtDraw.right / 2);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + m_rtDraw.bottom / 2);

	m_Rendering.Frame();
	return true;
}
bool Object::Render()
{
	DebugMode();

	m_Rendering.Render();

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
	return true;
}
void Object::DebugMode()
{
	if (S_Input.GetKey(VK_HOME) == KEYSTATE::KEY_PUSH)
	{
		isDebugMode = !isDebugMode;
	}
}
RECT Object::getCollisionRt()
{
	return m_rtCollision;
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
	m_DrawPos.x = x;
	m_DrawPos.y = y;

	m_rtDraw.left = l;
	m_rtDraw.top = t;
	m_rtDraw.bottom = b;
	m_rtDraw.right = r;

	m_CenterPos.x = m_DrawPos.x + (m_rtDraw.right * m_fZoom / 2);
	m_CenterPos.y = m_DrawPos.y + (m_rtDraw.bottom * m_fZoom / 2);

	FLOAT d = m_rtDraw.right * m_fZoom / 2;
	FLOAT e = m_rtDraw.bottom * m_fZoom / 2;

	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - d);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - e);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + d);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + e);

}

const RECT&	Object::getrtDraw() const
{
	return m_rtDraw;
}
const FloatPoint& Object::getDrawPos() const
{
	return m_DrawPos;
}
const HDC& Object::getColorDC() const
{
	return m_ColorBitmap->getMemDC();
}
const HDC&	Object::getMaskDC() const
{
	if (m_MaskBitmap == nullptr)
	{
		return nullptr;
	}
	return m_MaskBitmap->getMemDC();
}