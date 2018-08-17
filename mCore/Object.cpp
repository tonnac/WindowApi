#pragma once
#include "Object.h"
#include "InversionRendering.h"
#include "RotateRendering.h"

Object::Object() : m_ColorBitmap(nullptr), m_MaskBitmap(nullptr), isDebugMode(false),
					isDead(false), m_fSpeed(0.0f), m_pRendering(nullptr), m_fScroll(0.0f),
					isLanding(false)
{
	ZeroMemory(&m_CenterPos,sizeof(FloatPoint));
	ZeroMemory(&m_DrawPos, sizeof(FloatPoint));
	ZeroMemory(&m_rtDraw, sizeof(RECT));
	ZeroMemory(&m_rtCollision, sizeof(RECT));
}

bool Object::Init()
{
	m_pRendering = New Rendering(this);
	m_pRendering->Init();
	return true;
}
bool Object::Frame()
{
	m_pRendering->Frame();
	return true;
}
bool Object::Render()
{
	DebugMode();

	if(m_pRendering)
		m_pRendering->Render();

	if (isDebugMode)
	{
		int iPrev = SetROP2(g_hOffScreenDC, R2_NOTXORPEN);

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
	m_pRendering->Release();
	delete m_pRendering;
	return true;
}

RECT* Object::getrtDraw()
{
	return &m_rtDraw;
}
RECT* Object::getCollisionRt()
{
	return &m_rtCollision;
}
FloatPoint* Object::getDrawPos()
{
	return &m_DrawPos;
}
FloatPoint* Object::getCenterPos()
{
	return &m_CenterPos;
}
HDC Object::getColorDC() const
{
	return m_ColorBitmap->getMemDC();
}
HDC	Object::getMaskDC() const
{
	if (m_MaskBitmap == nullptr)
	{
		return nullptr;
	}
	return m_MaskBitmap->getMemDC();
}
FLOAT Object::getSpeed() const
{
	return m_fSpeed;
}
bool Object::getDebugmode() const
{
	return isDebugMode;
}
bool Object::getLanding() const
{
	return isLanding;
}

void Object::setRendering(const FLOAT& zoom, const INVERSE& type)
{
	if (m_pRendering)
	{
		m_pRendering->Release();
		delete m_pRendering;
	}
	m_pRendering = New InversionRendering(this, zoom, type);
	m_pRendering->Init();
}
void Object::setRendering(const FLOAT& rotation)
{
	if (m_pRendering)
	{
		m_pRendering->Release();
		delete m_pRendering;
	}
	m_pRendering = New RotateRendering(this, rotation);
	m_pRendering->Init();
}
void Object::setRendering(const INVERSE& type)
{
	m_pRendering->setInverse(type);
}
void Object::setDebugmode(const bool& bflag)
{
	isDebugMode = bflag;
}
void Object::setSpeed(const FLOAT& speed)
{
	m_fSpeed = speed;
}
void Object::setCenterPos_x(const FLOAT& ft)
{
	m_CenterPos.x = ft;
	m_DrawPos.x = ft + m_rtDraw.right / 2;

	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - m_rtDraw.right / 2);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - m_rtDraw.bottom / 2);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + m_rtDraw.right / 2);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + m_rtDraw.bottom / 2);
}
void Object::setCenterPos_y(const FLOAT& ft)
{
	m_CenterPos.y = ft;
	m_DrawPos.y = ft + m_rtDraw.bottom / 2;

	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - m_rtDraw.right / 2);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - m_rtDraw.bottom / 2);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + m_rtDraw.right / 2);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + m_rtDraw.bottom / 2);
}
void Object::setLanding(const bool& bflag)
{
	isLanding = bflag;
}
void Object::DebugMode()
{
	if (S_Input.GetKey(VK_HOME) == KEYSTATE::KEY_PUSH)
	{
		isDebugMode = !isDebugMode;
	}
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

	m_CenterPos.x = m_DrawPos.x + (m_rtDraw.right / 2);
	m_CenterPos.y = m_DrawPos.y + (m_rtDraw.bottom / 2);


	m_rtCollision.left = static_cast<LONG>(m_CenterPos.x - m_rtDraw.right / 2);
	m_rtCollision.top = static_cast<LONG>(m_CenterPos.y - m_rtDraw.bottom / 2);
	m_rtCollision.right = static_cast<LONG>(m_CenterPos.x + m_rtDraw.right / 2);
	m_rtCollision.bottom = static_cast<LONG>(m_CenterPos.y + m_rtDraw.bottom / 2);

	m_fScroll = static_cast<FLOAT>(m_rtDraw.left);

}

void Object::MoveScrollBk(const FLOAT& fsize)
{
	if (fsize < 0)
	{
		m_fScroll += (g_fPerSecFrame * g_fSpeed);
		m_rtDraw.left = static_cast<LONG>(m_fScroll);
	}
	else
	{
		m_fScroll += -(g_fPerSecFrame * g_fSpeed);
		m_rtDraw.left = static_cast<LONG>(m_fScroll);
	}
}
void Object::MoveScrollObj(const bool& bflag)
{
	if (bflag)
	{
		m_DrawPos.x += -(g_fPerSecFrame * g_fSpeed);
	}
	else
	{
		m_DrawPos.x += (g_fPerSecFrame * g_fSpeed);
	}
}