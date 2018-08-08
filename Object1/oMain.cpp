#include "Core.h"
#include "BkObject.h"
#include "NPCObj.h"
#include "Collision.h"

const int g_iMaxNpcCount = 10;

class KSample : public KCore
{
	std::vector<NPCObj>	m_npcList;
	Object				m_Hero;
	BkObject			m_BackGround;
public:
	bool Init()
	{
		m_npcList.resize(g_iMaxNpcCount);
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].LoadFile(L"../02_data/bitmap1.bmp", L"../02_data/bitmap2.bmp");
			m_npcList[iObj].Set(static_cast<float>(100.0 + rand() % 500), 100 + rand() % 100, 115, 62, 36, 35);
			m_npcList[iObj].Init();
		}
		m_BackGround.LoadFile(L"../02_data/bk.bmp");
		m_Hero.LoadFile(L"../02_data/bitmap1.bmp", L"../02_data/bitmap2.bmp");
		m_Hero.Set(500, 500, 133, 1, 42, 59);
		m_BackGround.Set(g_rtClient.right / 2 , g_rtClient.bottom / 2, 0, 0, g_rtClient.right, g_rtClient.bottom);
		m_BackGround.Init();
		m_Hero.Init();
		return true;
	}
	bool Frame()
	{
		if (I_KInput.getKey('0') == KEY_PUSH)
		{
			m_Hero.isDebugMode = !m_Hero.isDebugMode;
			for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
			{
				m_npcList[iObj].isDebugMode = !m_npcList[iObj].isDebugMode;
			}
		}
		m_BackGround.Frame();
		m_Hero.Frame();
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Frame();
		}

		for (int i = 0; i < g_iMaxNpcCount; ++i)
		{
			if (Collision::SphereInSphere(m_Hero.m_rtCollision, m_npcList[i].m_rtCollision))
			{
				m_npcList[i].isDead = true;
			}
			if (I_KInput.getMouse(VK_LBUTTON) == KEY_PUSH && Collision::SphereInPoint(m_npcList[i].m_rtCollision, I_KInput.getMousePos()))
			{
				m_npcList[i].isDead = true;
			}
		}
		return true;
	}
	bool Render()
	{

		m_BackGround.Render();
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			if (!m_npcList[iObj].isDead)
			{
				m_npcList[iObj].Render();
			}
		}
		m_Hero.Render();
		return true;
	}
	bool Release()
	{
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Release();
		}
		m_BackGround.Release();
		m_Hero.Release();
		return true;
	}
private:
};



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPWSTR szCmdLine, int nCmdShow)
{
	KSample wd;
	wd.SetWindow(hInst, 800, 600);
	wd.Run();
	return 0;
}