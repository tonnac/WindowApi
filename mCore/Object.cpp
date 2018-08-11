#include "Object.h"

Object::Object()
{
	m_ColorBitmap = nullptr;
	m_MaskBitmap = nullptr;
	isDebugMode = false;
	m_sRotation = -1;
	m_rtZoom = nullptr;
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
	return true;
}
bool Object::Frame()
{
	if (S_Input.GetKey(VK_INSERT) == KEYSTATE::KEY_PUSH)
	{
		if (m_sRotation < 0)
		{
			m_sRotation = TB_ROTATION;
		}
		else
		{
			m_sRotation = -1;
		}
	}
	if (S_Input.GetKey('W') == KEYSTATE::KEY_PUSH ||
		S_Input.GetKey('W') == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos.y += (-1 * g_fPerSecFrame * 1000.f);
	}
	if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH ||
		S_Input.GetKey('S') == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos.y += (1 * g_fPerSecFrame * 1000.f);
	}
	if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH ||
		S_Input.GetKey('A') == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos.x += (-1 * g_fPerSecFrame * 1000.f);
	}
	if (S_Input.GetKey('D') == KEYSTATE::KEY_PUSH ||
		S_Input.GetKey('D') == KEYSTATE::KEY_HOLD)
	{
		m_CenterPos.x += (1 * g_fPerSecFrame * 1000.f);
	}

	m_DrawPos.x = m_CenterPos.x - (m_rtDraw.right / 2);
	m_DrawPos.y = m_CenterPos.y - (m_rtDraw.bottom / 2);

	m_rtCollision.left = m_DrawPos.x;
	m_rtCollision.top = m_DrawPos.y;
	m_rtCollision.right = m_DrawPos.x + m_rtDraw.right;
	m_rtCollision.bottom = m_DrawPos.y + m_rtDraw.bottom;

	return true;
}
bool Object::Render()
{

	if (m_rtZoom != nullptr || m_sRotation > 0)
	{
		InversionRender();
	}
	else
	{
		NormalRender();
	}
	if (isDebugMode)
	{
		int iPrev = SetROP2(g_hOffScreenDC, R2_MASKPEN);
		Rectangle(g_hOffScreenDC, m_rtCollision.left, m_rtCollision.top,
			m_rtCollision.right, m_rtCollision.bottom);
		SetROP2(g_hOffScreenDC, iPrev);
	}
	return true;
}
bool Object::Release()
{
	if (m_rtZoom != nullptr)
	{
		delete m_rtZoom;
	}
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
void Object::Set(const float& x, const float& y,
	const DWORD& l, const DWORD& t, const DWORD& r, const DWORD& b)
{
	m_CenterPos.x = x;
	m_CenterPos.y = y;

	m_DrawPos.x = x - (r / 2);
	m_DrawPos.y = y - (b / 2);

	m_rtDraw.left = l;
	m_rtDraw.top = t;
	m_rtDraw.bottom = b;
	m_rtDraw.right = r;

	m_rtCollision.left = m_DrawPos.x;
	m_rtCollision.top = m_DrawPos.y;
	m_rtCollision.right = m_DrawPos.x + m_rtDraw.right;
	m_rtCollision.bottom = m_DrawPos.y + m_rtDraw.bottom;
}
void Object::SetInverse(SHORT Key, RECT * rt)
{
	Key = m_sRotation;
	m_rtZoom = rt;
}
bool Object::NormalRender()
{
	HDC ColorDC = m_ColorBitmap->getMemDC();
	if (m_MaskBitmap == nullptr)
	{
		BitBlt(g_hOffScreenDC, m_DrawPos.x, m_DrawPos.y,
			m_rtDraw.right, m_rtDraw.bottom,
			ColorDC,
			m_rtDraw.left, m_rtDraw.top, SRCCOPY);
		return true;
	}
	HDC MaskDC = m_MaskBitmap->getMemDC();
	BitBlt(g_hOffScreenDC, m_DrawPos.x, m_DrawPos.y,
		m_rtDraw.right, m_rtDraw.bottom,
		MaskDC,
		m_rtDraw.left, m_rtDraw.top, SRCAND);
	BitBlt(g_hOffScreenDC, m_DrawPos.x, m_DrawPos.y,
		m_rtDraw.right, m_rtDraw.bottom,
		ColorDC,
		m_rtDraw.left, m_rtDraw.top, SRCINVERT);
	BitBlt(g_hOffScreenDC, m_DrawPos.x, m_DrawPos.y,
		m_rtDraw.right, m_rtDraw.bottom,
		MaskDC,
		m_rtDraw.left, m_rtDraw.top, SRCINVERT);
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
				m_DrawPos.x + m_rtDraw.right, m_DrawPos.y,
				-m_rtDraw.right, m_rtDraw.bottom,
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCCOPY);
			break;
		case TB_ROTATION:
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x, m_DrawPos.y + m_rtDraw.bottom,
				m_rtDraw.right, -m_rtDraw.bottom,
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCCOPY);
			break;
		case LRTB_ROTATION:
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x + m_rtDraw.right, m_DrawPos.y + m_rtDraw.bottom,
				-m_rtDraw.right, -m_rtDraw.bottom,
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCCOPY);
			break;
		default:
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x, m_DrawPos.y,
				m_rtZoom->right, m_rtZoom->bottom,
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
				m_DrawPos.x + m_rtDraw.right, m_DrawPos.y,
				-m_rtDraw.right, m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x + m_rtDraw.right, m_DrawPos.y,
				-m_rtDraw.right, m_rtDraw.bottom,
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x + m_rtDraw.right, m_DrawPos.y,
				-m_rtDraw.right, m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			break;
		case TB_ROTATION:
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x, m_DrawPos.y + m_rtDraw.bottom,
				m_rtDraw.right, -m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x, m_DrawPos.y + m_rtDraw.bottom,
				m_rtDraw.right, -m_rtDraw.bottom,
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x, m_DrawPos.y + m_rtDraw.bottom,
				m_rtDraw.right, -m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			break;
		case LRTB_ROTATION:
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x + m_rtDraw.right, m_DrawPos.y + m_rtDraw.bottom,
				-m_rtDraw.right, -m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x + m_rtDraw.right, m_DrawPos.y + m_rtDraw.bottom,
				-m_rtDraw.right, -m_rtDraw.bottom,
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x + m_rtDraw.right, m_DrawPos.y + m_rtDraw.bottom,
				-m_rtDraw.right, -m_rtDraw.bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			break;
		default:
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x, m_DrawPos.y,
				m_rtZoom->right, m_rtZoom->bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x, m_DrawPos.y,
				m_rtZoom->right, m_rtZoom->bottom,
				ColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				m_DrawPos.x, m_DrawPos.y,
				m_rtZoom->right, m_rtZoom->bottom,
				MaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
		}
	}
	return true;
}