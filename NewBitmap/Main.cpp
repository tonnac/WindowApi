#include "Core.h"


struct KPoint
{
	float x, y;
};

class KSample : public KCore
{
	KPoint m_pos;
	Bitmap m_bBitmap[2];
public:
	bool Init()
	{
		m_bBitmap[0].Init();
		m_bBitmap[0].LoadFile(L"../02_data/Number.bmp");
		m_bBitmap[1].Init();
		m_bBitmap[1].LoadFile(L"../02_data/86754.bmp");
		m_pos.x = m_pos.y = 80.0f;
		return true;
	}
	bool Frame()
	{
		if (I_KInput.getKey('A'))
		{
			m_pos.x += (-1 * g_fSecPerFrame * 200.0f);
		}
		if (I_KInput.getKey('D'))
		{
			m_pos.x += (1 * g_fSecPerFrame * 200.0f);
		}
		if (I_KInput.getKey('W'))
		{
			m_pos.y += (-1 * g_fSecPerFrame * 200.0f);
		}
		if (I_KInput.getKey('S'))
		{
			m_pos.y += (1 * g_fSecPerFrame * 200.0f);
		}
		if (I_KInput.getMouse(VK_MBUTTON) == KEY_PUSH)
		{
			MessageBox(nullptr, L"KEY_PUSH", L"LBUTTON", MB_OK);
		}
		m_bBitmap[0].Frame();
		return true;
	}
	bool Render()
	{
		static DWORD frame = 0;
		HDC MemDC = m_bBitmap[0].getMemDC();
		HDC MemDC1 = m_bBitmap[1].getMemDC();
		Sleep(100);
		BitBlt(g_hOffScreenDC, m_pos.x, m_pos.y, 47, 48, MemDC, 1 + (frame * 48), 0, SRCCOPY);
		TransparentBlt(g_hOffScreenDC, 200, 500, 48, 48, MemDC1, (1 + frame) + (frame * 48),75,48, 48, RGB(8,255,68));
		frame = (++frame) % 7;
		return m_bBitmap[0].Render();
	}
	bool Release()
	{
		return m_bBitmap[0].Release();
	}
private:
};



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPWSTR szCmdLine, int nCmdShow)
{
	KSample wd;
	wd.SetWindow(hInst);
	wd.Run();
	return 0;
}