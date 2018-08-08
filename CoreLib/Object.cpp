#include "Object.h"
#include "Input.h"

#pragma comment(lib,"msimg32.lib") // transparentblt()

void Object::Set(const KPoint& pos)
{
	m_DrawPos = pos;
}
void Object::Set(float x, float y, DWORD l, DWORD t, DWORD r, DWORD b)
{
	m_CenterPos.x = x;
	m_CenterPos.y = y;
	m_DrawPos.x = x - (r / 2);
	m_DrawPos.y = y - (b / 2);
	m_rtDraw.left = l;
	m_rtDraw.right = r;
	m_rtDraw.bottom = b;
	m_rtDraw.top = t;
	m_rtCollision.left = l;
	m_rtCollision.right = l+r;
	m_rtCollision.top = t;
	m_rtCollision.bottom = t+b;
}

bool Object::LoadFile(const TCHAR* pszColor, const TCHAR* pszMask)
{
	int index;
	if (pszMask != nullptr)
	{
		index = I_BitmapMgr.Load(pszMask);
		m_pMaskBitmap = I_BitmapMgr.getPtr(index);
	}
	index = I_BitmapMgr.Load(pszColor);
	m_pColorBitmap = I_BitmapMgr.getPtr(index);
	return true;
}
bool Object::Init()
{
	isDead = false;
	return true;
}
bool Object::Frame()
{
	if (I_KInput.getKey('A'))
	{
		m_CenterPos.x += (-1 * g_fSecPerFrame * 350.0f);
	}
	if (I_KInput.getKey('D'))
	{
		m_CenterPos.x += (1 * g_fSecPerFrame * 350.0f);
	}
	if (I_KInput.getKey('W'))
	{
		m_CenterPos.y += (-1 * g_fSecPerFrame * 350.0f);
	}
	if (I_KInput.getKey('S'))
	{
		m_CenterPos.y += (1 * g_fSecPerFrame * 350.0f);
	}
	if (I_KInput.getMouse(VK_MBUTTON) == KEY_PUSH)
	{
		MessageBox(nullptr, L"KEY_PUSH", L"MBUTTON", MB_OK);
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
	if (m_pMaskBitmap == nullptr)
	{
		BitBlt(g_hOffScreenDC, 
			m_DrawPos.x, m_DrawPos.y,
			m_rtDraw.right, 
			m_rtDraw.bottom, 
			m_pColorBitmap->m_hMemDC, 
			m_rtDraw.left, m_rtDraw.top, 
			SRCCOPY);
		return true;
	}
	BitBlt(g_hOffScreenDC, 
		m_DrawPos.x, m_DrawPos.y,
		m_rtDraw.right, 
		m_rtDraw.bottom, 
		m_pMaskBitmap->m_hMemDC, 
		m_rtDraw.left, m_rtDraw.top, 
		SRCAND);
	BitBlt(g_hOffScreenDC, 
		m_DrawPos.x, m_DrawPos.y,
		m_rtDraw.right, 
		m_rtDraw.bottom, 
		m_pColorBitmap->m_hMemDC, 
		m_rtDraw.left, m_rtDraw.top, 
		SRCINVERT);
	BitBlt(g_hOffScreenDC, 
		m_DrawPos.x, m_DrawPos.y,
		m_rtDraw.right, 
		m_rtDraw.bottom, 
		m_pMaskBitmap->m_hMemDC, 
		m_rtDraw.left, m_rtDraw.top, 
		SRCINVERT);
	if (isDebugMode)
	{
		int iPrev = SetROP2(g_hOffScreenDC, R2_MASKPEN);
		LONG dwX = m_rtDraw.right;
		LONG dwY = m_rtDraw.bottom;
		LONG ok = (dwX < dwY) ? dwY : dwX;
		Ellipse(g_hOffScreenDC,
			m_rtCollision.left, m_rtCollision.top,
			m_rtCollision.left + ok,
			m_rtCollision.top + ok);
		//Rectangle(g_hOffScreenDC,
		//	m_rtCollision.left, m_rtCollision.top,
		//	m_rtCollision.right,
		//	m_rtCollision.bottom);
		SetROP2(g_hOffScreenDC, iPrev);
	}
	return true;
}
bool Object::Release()
{
	return true;
}

bool Object::Draw(SHORT sType, RECT* rt)
{
	RECT rtDraw = m_rtDraw;
	if (rt != nullptr)
	{
		rtDraw = *rt;
	}
	switch (sType)
	{
	case LR_ROTATION:
		StretchBlt(g_hOffScreenDC,
			m_DrawPos.x + rtDraw.right, m_DrawPos.y,
			-rtDraw.right,
			rtDraw.bottom,
			m_pColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	case TB_ROTATION:
		StretchBlt(g_hOffScreenDC,
			m_DrawPos.x, m_DrawPos.y + rtDraw.bottom,
			rtDraw.right,
			-rtDraw.bottom,
			m_pColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	case LRTB_ROTATION:
		StretchBlt(g_hOffScreenDC,
			m_DrawPos.x + rtDraw.right, m_DrawPos.y + rtDraw.bottom,
			-rtDraw.right,
			-rtDraw.bottom,
			m_pColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	default:
		StretchBlt(g_hOffScreenDC,
			m_DrawPos.x + rtDraw.right, m_DrawPos.y,
			rtDraw.right,
			rtDraw.bottom,
			m_pColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
	}
	return true;
}
bool Object::DrawColorKey(DWORD maskColor)
{
	TransparentBlt(g_hOffScreenDC,
		m_DrawPos.x, m_DrawPos.y,
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_pColorBitmap->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		m_rtDraw.right, m_rtDraw.bottom,
		maskColor);
	return true;
}

Object::Object() : m_pColorBitmap(nullptr), m_pMaskBitmap(nullptr)
{
	m_DrawPos.x = 0;
	m_DrawPos.y = 0;
	m_fDir[0] = (rand() % 2) ? -1.0f : 1.0f;
	m_fDir[1] = (rand() % 2) ? -1.0f : 1.0f;
	isDebugMode = false;
	isDead = false;
}
Object::~Object()
{
}
