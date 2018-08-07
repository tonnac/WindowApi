#include "Core.h"

#pragma comment(lib,"msimg32.lib")

class KSample : public KCore
{
	KPoint m_pos;
	Bitmap m_bBitmap;
public:
	bool Init()
	{
		m_bBitmap.Init();
		m_bBitmap.LoadFile(L"../02_data/86754.bmp");
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
		m_bBitmap.Frame();
		return true;
	}
	bool Render()
	{
		static DWORD frame = 0;
		Sleep(10);
		// 1, 75, 48, 48 
	//	BitBlt(g_hOffScreenDC, m_pos.x, m_pos.y, 47, 48, m_bBitmap.m_hMemDC, 1 + frame + (frame * 48), 75, SRCCOPY);
		int x = 200;
		int y = 200;
		TransparentBlt(g_hOffScreenDC, 
			m_pos.x + x, m_pos.y + y, 
			x, y, 
			m_bBitmap.m_hMemDC, 
			1 + frame + (frame * 48), 75, 
			47, 48, RGB(255,255,255));
		frame = (++frame) % 7;
		return m_bBitmap.Render();
	}
	bool Release()
	{
		return m_bBitmap.Release();
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