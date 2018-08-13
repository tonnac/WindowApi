#include "InversionRendering.h"

InversionRendering::InversionRendering(Object* ob, const SHORT& inverse, const FLOAT& zoom) : Rendering(ob),
																		m_sInverse(inverse), m_fZoom(zoom)
{}

bool InversionRendering::Frame()
{

}
bool InversionRendering::Render()
{
	if (m_hMaskDC == nullptr)
	{
		switch (m_sInverse)
		{
		case LR_ROTATION:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(-m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				m_hColorDC,
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
				m_hColorDC,
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
				m_hColorDC,
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
				m_hColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCCOPY);
		}
	}
	else
	{
		switch (m_sInverse)
		{
		case LR_ROTATION:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right * m_fZoom),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(-m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				m_hMaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right * m_fZoom),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(-m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				m_hColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right * m_fZoom),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(-m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				m_hMaskDC,
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
				m_hMaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				m_rtDraw.right, -m_rtDraw.bottom,
				m_hColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				m_rtDraw.right, -m_rtDraw.bottom,
				m_hMaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			break;
		case LRTB_ROTATION:
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				-m_rtDraw.right, -m_rtDraw.bottom,
				m_hMaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				-m_rtDraw.right, -m_rtDraw.bottom,
				m_hColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x + m_rtDraw.right),
				static_cast<int>(m_DrawPos.y + m_rtDraw.bottom),
				-m_rtDraw.right, -m_rtDraw.bottom,
				m_hMaskDC,
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
				m_hMaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCAND);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				m_hColorDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
			StretchBlt(g_hOffScreenDC,
				static_cast<int>(m_DrawPos.x),
				static_cast<int>(m_DrawPos.y),
				static_cast<int>(m_rtDraw.right * m_fZoom),
				static_cast<int>(m_rtDraw.bottom * m_fZoom),
				m_hMaskDC,
				m_rtDraw.left, m_rtDraw.top,
				m_rtDraw.right, m_rtDraw.bottom,
				SRCINVERT);
		}
	}
	return true;
}