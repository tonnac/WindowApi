#include "Bitmap.h"

bool Bitmap::LoadFile(T_STR szLoadFile)
{
	HDC hdc = GetDC(g_hWnd);
	m_hBitmap = static_cast<HBITMAP>(LoadImage(g_hInstance,
		szLoadFile.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE
	));
	if (m_hBitmap != nullptr)
	{
		GetObject(m_hBitmap, sizeof(BITMAP), &m_bmpInfo);
		m_hMemDC = CreateCompatibleDC(hdc);
		SelectObject(m_hMemDC, m_hBitmap);
		m_szName = szLoadFile;
		ReleaseDC(g_hWnd, hdc);
		return true;
	}
	return false;
}
T_STR Bitmap::getName()
{
	return m_szName;
}
void Bitmap::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}
void Bitmap::SetOffset(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
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
	HDC hdc = GetDC(g_hWnd);
	BitBlt(hdc, 0, 0, m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, m_hMemDC, 0, 0, SRCCOPY);
	ReleaseDC(g_hWnd,hdc);
	return true;
}
bool Bitmap::Release()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
	return true;
}
Bitmap::Bitmap()
{

}
Bitmap::~Bitmap()
{

}