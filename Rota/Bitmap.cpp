#include "Bitmap.h"

bool Bitmap::Init()
{
	return true;
}
bool Bitmap::Frame()
{
	return true;
}
bool Bitmap::Render()
{
	return true;
}
bool Bitmap::Release()
{
	return true;
}
bool Bitmap::LoadFile(const TCHAR* szFileName)
{
	HDC hdc = GetDC(g_hWnd);
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, szFileName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	assert(m_hBitmap != nullptr);
	m_hMemDC = CreateCompatibleDC(hdc);
	SelectObject(m_hMemDC, m_hBitmap);
	return true;
}
void Bitmap::Set(float x, float y, LONG l, LONG t, LONG r, LONG b)
{
	m_CenterPos.x = x;
	m_CenterPos.y = y;

	m_DrasPos.x = x - (r / 2);
	m_DrasPos.y = y - (b / 2);

	m_rtDraw.left = l;
	m_rtDraw.right = r;
	m_rtDraw.bottom = b;
	m_rtDraw.top = t;
}