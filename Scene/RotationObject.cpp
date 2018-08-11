#include "RotationObject.h"

bool RotationObject::Init()
{
	m_hScreecDC = GetDC(g_hWnd);
	m_hColorDC = CreateCompatibleDC(m_hScreecDC);
	m_hMaskDC = CreateCompatibleDC(m_hScreecDC);
	m_rtDraw = { 133,1,42,59 };
	m_rtDrawPos = { 200,200 };
	m_CenterPos = { m_rtDrawPos.x + m_rtDraw.right / 2, m_rtDrawPos.y + m_rtDraw.bottom };
	m_hColorBitmap = (HBITMAP)LoadImage(g_hInstance, L"../02_data/bitmap1.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_hMaskBitmap = (HBITMAP)LoadImage(g_hInstance, L"../02_data/bitmap2.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
}
bool RotationObject::Frame()
{
	return true;
}
bool RotationObject::Render()
{
	
}
bool RotationObject::Release()
{

}