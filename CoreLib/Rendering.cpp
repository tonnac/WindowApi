#include "Rendering.h"
#include "Object.h"

Rendering::Rendering(const Object& ob) : m_DrawPos(ob.getDrawPos()), m_rtDraw(ob.getrtDraw()),
										 m_hColorDC(ob.getColorDC()), m_hMaskDC(ob.getMaskDC())
{}

bool Rendering::Init()
{
	return true;
}
bool Rendering::Frame()
{
	return true;
}
bool Rendering::Render()
{
	if (m_hMaskDC == nullptr)
	{
		BitBlt(g_hOffScreenDC,
			static_cast<int>(m_DrawPos.x),
			static_cast<int>(m_DrawPos.y),
			m_rtDraw.right,
			m_rtDraw.bottom,
			m_hColorDC,
			m_rtDraw.left,
			m_rtDraw.top,
			SRCCOPY);
		return true;
	}
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_DrawPos.x),
		static_cast<int>(m_DrawPos.y),
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_hMaskDC,
		m_rtDraw.left,
		m_rtDraw.top, SRCAND);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_DrawPos.x),
		static_cast<int>(m_DrawPos.y),
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_hColorDC,
		m_rtDraw.left,
		m_rtDraw.top,
		SRCINVERT);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_DrawPos.x),
		static_cast<int>(m_DrawPos.y),
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_hMaskDC,
		m_rtDraw.left,
		m_rtDraw.top,
		SRCINVERT);
	return true;
}
bool Rendering::Release()
{
	return true;
}
