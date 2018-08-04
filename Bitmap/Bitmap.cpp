#include "Bitmap.h"

HDC	g_hOffScreenDC = nullptr;

Bitmap::Bitmap()
{
	m_kPos.x = 100;
	m_kPos.y = 100;
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
	HDC hdc = GetDC(g_hWnd);
	g_hOffScreenDC = CreateCompatibleDC(hdc);
	m_hofbit = CreateCompatibleBitmap(hdc, g_rtClient.right, g_rtClient.bottom);
	SelectObject(g_hOffScreenDC, m_hofbit);

	COLORREF bkColor = RGB(255, 255, 120);
	m_hBkColor = CreateSolidBrush(bkColor);
	SelectObject(g_hOffScreenDC, m_hBkColor);

	ReleaseDC(g_hWnd, hdc);
	return true;
}
bool Bitmap::Frame()
{
	PatBlt(g_hOffScreenDC, 0, 0, g_rtClient.right, g_rtClient.bottom, PATCOPY);
	return true;
}
bool Bitmap::Render()
{
	HDC hdc = GetDC(g_hWnd);
	BitBlt(hdc, 0,0, g_rtClient.right, g_rtClient.bottom, g_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}
bool Bitmap::Release()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
	return true;
}