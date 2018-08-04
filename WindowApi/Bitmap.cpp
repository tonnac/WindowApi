#include "Bitmap.h"

HDC	g_hOffScreenDC = nullptr;

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
	ReleaseDC(g_hWnd, hdc);
	return true;
}

bool Bitmap::Init()
{
	HDC hdc = GetDC(g_hWnd);
	g_hOffScreenDC = CreateCompatibleDC(hdc);
	m_hofbit = CreateCompatibleBitmap(hdc, g_rtClient.right, g_rtClient.bottom);
	GetObject(m_hofbit, sizeof(BITMAP), &m_bBmpInfo);
	SelectObject(g_hOffScreenDC, m_hofbit);

	COLORREF bkColor = RGB(0, 70, 50);
	m_hBkColor = CreateSolidBrush(bkColor);
	SelectObject(g_hOffScreenDC, m_hBkColor);

	ReleaseDC(g_hWnd, hdc);
	return true;
}
bool Bitmap::Frame()
{
	//HDC hdc = GetDC(g_hWnd);
	PatBlt(g_hOffScreenDC, 0, 0, g_rtClient.right, g_rtClient.bottom, PATCOPY);
	return true;
}
bool Bitmap::Render()
{
	HDC hdc = GetDC(g_hWnd);
	
	BitBlt(hdc, 0,0, g_rtClient.right, g_rtClient.bottom,g_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}
bool Bitmap::Release()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
	return true;
}