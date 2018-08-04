#include "Bitmap.h"

HDC	g_hOffScreenDC = nullptr;

Bitmap::Bitmap()
{
	m_kPos.x = 100;
	m_kPos.y = 100;
}

void Bitmap::setOffset(float x, float y)
{
	m_kPos.x += x;
	m_kPos.y += y;
}
float Bitmap::getPos(float fValue)
{
	return (fValue == 0.0f) ? m_kPos.x : m_kPos.y;
}
BITMAP Bitmap::getBmpInfo()
{
	return m_bBmpInfo;
}
HDC&	Bitmap::getMemDC()
{
	return m_hMemDC;
}

bool Bitmap::LoadFile(T_STR szFileName)
{
	HDC hdc = GetDC(g_hWnd);
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, szFileName.c_str(),
		IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (m_hBitmap == nullptr)
	{
		return false;
	}
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bBmpInfo);
	m_hMemDC = CreateCompatibleDC(hdc);
	SelectObject(m_hMemDC, m_hBitmap);
	m_szFileName = szFileName;
	return true;
}

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
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
	return true;
}