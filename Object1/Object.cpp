#include "Object.h"
#include "Input.h"

#pragma comment(lib,"msimg32.lib") // transparentblt()

void Object::Set(const KPoint& pos)
{
	m_pos = pos;
}
void Object::Set(float x, float y, DWORD l, DWORD t, DWORD r, DWORD b)
{
	m_pos.x = x;
	m_pos.y = y;
	m_rtDraw.left = l;
	m_rtDraw.right = r;
	m_rtDraw.bottom = b;
	m_rtDraw.top = t;
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
	return true;
}
bool Object::Frame()
{
	if (I_KInput.getKey('A'))
	{
		m_pos.x += (-1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('D'))
	{
		m_pos.x += (1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('W'))
	{
		m_pos.y += (-1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('S'))
	{
		m_pos.y += (1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getMouse(VK_MBUTTON) == KEY_PUSH)
	{
		MessageBox(nullptr, L"KEY_PUSH", L"MBUTTON", MB_OK);
	}
	return true;
}
bool Object::Render()
{
	if (m_pMaskBitmap == nullptr)
	{
		BitBlt(g_hOffScreenDC, 
			m_pos.x, m_pos.y, 
			m_rtDraw.right, 
			m_rtDraw.bottom, 
			m_pColorBitmap->m_hMemDC, 
			m_rtDraw.left, m_rtDraw.top, 
			SRCCOPY);
		return true;
	}
	BitBlt(g_hOffScreenDC, 
		m_pos.x, m_pos.y, 
		m_rtDraw.right, 
		m_rtDraw.bottom, 
		m_pMaskBitmap->m_hMemDC, 
		m_rtDraw.left, m_rtDraw.top, 
		SRCAND);
	BitBlt(g_hOffScreenDC, 
		m_pos.x, m_pos.y, 
		m_rtDraw.right, 
		m_rtDraw.bottom, 
		m_pColorBitmap->m_hMemDC, 
		m_rtDraw.left, m_rtDraw.top, 
		SRCINVERT);
	BitBlt(g_hOffScreenDC, 
		m_pos.x, m_pos.y, 
		m_rtDraw.right, 
		m_rtDraw.bottom, 
		m_pMaskBitmap->m_hMemDC, 
		m_rtDraw.left, m_rtDraw.top, 
		SRCINVERT);
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
			m_pos.x + rtDraw.right, m_pos.y,
			-rtDraw.right,
			rtDraw.bottom,
			m_pColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	case TB_ROTATION:
		StretchBlt(g_hOffScreenDC,
			m_pos.x, m_pos.y + rtDraw.bottom,
			rtDraw.right,
			-rtDraw.bottom,
			m_pColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	case LRTB_ROTATION:
		StretchBlt(g_hOffScreenDC,
			m_pos.x + rtDraw.right, m_pos.y + rtDraw.bottom,
			-rtDraw.right,
			-rtDraw.bottom,
			m_pColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	default:
		StretchBlt(g_hOffScreenDC,
			m_pos.x + rtDraw.right, m_pos.y,
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
		m_pos.x, m_pos.y,
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
	m_pos.x = 0; 
	m_pos.y = 0;
}
Object::~Object()
{
}
