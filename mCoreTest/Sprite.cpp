#include "Sprite.h"

bool Sprite::Init()
{

	m_DrawPos.x = 200;
	m_DrawPos.y = 200;

	m_fSpriteTime = 0.0f;
	m_fDivideTime = 1.0f;
	m_iIndex = 0;

	m_fOffset = m_fDivideTime / m_spritelist.size();

	return true;
}
bool Sprite::Frame()
{
	PreFrame();
	Object::Frame();
	return true;
}
//bool Sprite::Render()
//{
//	return true;
//}
bool Sprite::Release()
{
	return true;
}
bool Sprite::AddRect(const RECT& rt)
{
	m_spritelist.push_back(rt);
	return true;
}
bool Sprite::SetRect(const RECT& rt)
{
	m_rtDraw.left = rt.left;
	m_rtDraw.right = rt.right;
	m_rtDraw.bottom = rt.bottom;
	m_rtDraw.top = rt.top;
	return true;
}
bool Sprite::SetDivideTime(const FLOAT& offset)
{
	m_fDivideTime = offset;
	return true;
}
bool Sprite::PreFrame()
{
	m_fSpriteTime += g_fPerSecFrame;
	if (m_fSpriteTime >= m_fOffset)
	{
		m_fSpriteTime -= m_fOffset;
		if (++m_iIndex >= m_spritelist.size())
		{
			m_iIndex = 0;
		}
		m_rtDraw = m_spritelist[m_iIndex];
	}
	return true;
}