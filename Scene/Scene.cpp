#include "Scene.h"

bool Scene::Init()
{
	return true;
}
bool Scene::Frame()
{
	return true;
}
bool Scene::Render()
{
	return true;
}
bool Scene::Release()
{
	return true;
}
bool Scene::Reset()
{
	return true;
}
Scene::Scene(int n) : m_iSceneID(n), m_bNextSceneStart(false), m_fDownScene(1.0f)
{
}
Scene::~Scene()
{
}

bool LobbyScene::Init()
{
	m_BackGround.LoadFile(L"../02_data/bk.bmp");
	m_BackGround.Set(g_rtClient.right / 2, -g_rtClient.bottom / 2, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_BackGround.Init();
	m_btnStart.LoadFile(L"../02_data/main_start_nor.bmp");
	m_btnStart.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0,334, 82);
	m_btnStart.Init();
	return true;
}
bool LobbyScene::Frame()
{
//	Sleep(10);
	if (m_fDownScene != static_cast<float>(g_rtClient.bottom))
	{
		m_fDownScene += 0.5f;
		m_BackGround.Set(g_rtClient.right / 2, -g_rtClient.bottom / 2 + m_fDownScene, 0, 0, g_rtClient.right, g_rtClient.bottom);
	}
	Sleep(1);
	m_BackGround.Frame();

	m_btnStart.Frame();
	if (m_fDownScene == static_cast<float>(g_rtClient.bottom))
	{
		if (I_KInput.getMouse(VK_LBUTTON) == KEY_UP && Collision::RectInPoint(m_btnStart.m_rtCollision, I_KInput.getMousePos()))
		{
			m_bNextSceneStart = true;
		}
	}
	return true;
}
bool LobbyScene::Render()
{
	m_BackGround.Render();
	if (m_fDownScene == static_cast<float>(g_rtClient.bottom))
	{
		m_btnStart.Render();
	}
	return true;
}
bool LobbyScene::Release()
{
	m_BackGround.Release();
	m_btnStart.Release();
	return true;
}
bool LobbyScene::Reset()
{
	return true;
}
LobbyScene::LobbyScene() : Scene(1)
{
}
LobbyScene::~LobbyScene()
{
}

bool GameScene::Init()
{
	m_npcList.resize(g_iMaxNpcCount);
	for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
	{
		m_npcList[iObj].LoadFile(L"../02_data/bitmap1.bmp", L"../02_data/bitmap2.bmp");
		m_npcList[iObj].Set(static_cast<float>(100.0 + rand() % 500), 100 + rand() % 100, 115, 62, 36, 35);
		m_npcList[iObj].Init();
	}
	m_BackGround.LoadFile(L"../02_data/binglybongly_wallpaper.bmp");
	m_Hero.LoadFile(L"../02_data/bitmap1.bmp", L"../02_data/bitmap2.bmp");
	m_Hero.Set(500, 500, 133, 1, 42, 59);
	m_BackGround.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_BackGround.Init();
	m_Hero.Init();
	return true;
}
bool GameScene::Frame()
{
	if (I_KInput.getKey('0') == KEY_PUSH)
	{
		m_Hero.isDebugMode = !m_Hero.isDebugMode;
		for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].isDebugMode = !m_npcList[iObj].isDebugMode;
		}
	}
	m_BackGround.Frame();
	m_Hero.Frame();
	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
	{
		m_npcList[iObj].Frame();
	}

	for (int i = 0; i < m_iMaxNpcCount; ++i)
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
	if (I_KInput.getMouse(VK_RBUTTON) == KEY_UP)
	{
		for (int i = 0; i < m_iMaxNpcCount; ++i)
		{
			m_npcList[i].isDead = true;
		}
	}
	bool bNextScene = true;
	for (int iNpc = 0; iNpc < m_iMaxNpcCount; ++iNpc)
	{
		if (m_npcList[iNpc].isDead == false)
		{
			bNextScene = false;
		}
	}
	if (bNextScene == true)
	{
		m_bNextSceneStart = true;
	}
	return true;
}
bool GameScene::Render()
{

	m_BackGround.Render();
	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
	{
		if (!m_npcList[iObj].isDead)
		{
			m_npcList[iObj].Render();
		}
	}
	m_Hero.Render();
	return true;
}
bool GameScene::Release()
{
	for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
	{
		m_npcList[iObj].Release();
	}
	m_BackGround.Release();
	m_Hero.Release();
	return true;
}
bool GameScene::Reset()
{
	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
	{
		m_npcList[iObj].Init();
		m_npcList[iObj].Set(static_cast<float>(100.0 + rand() % 500), 100 + rand() % 100, 115, 62, 36, 35);
	}
	m_bNextSceneStart = false;
	return true;
}
GameScene::GameScene() : Scene(2)
{
}
GameScene::~GameScene()
{
}

bool EndScene::Init()
{
	m_BackGround.LoadFile(L"../02_data/RAINBOW.bmp");
	m_BackGround.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_BackGround.Init();
	m_btnStart.LoadFile(L"../02_data/end.bmp");
	m_btnStart.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 100, 50);
	m_btnStart.Init();
	return true;
}
bool EndScene::Frame()
{
	m_BackGround.Frame();
	m_btnStart.Frame();
	if (I_KInput.getMouse(VK_LBUTTON) == KEY_UP && Collision::RectInPoint(m_btnStart.m_rtCollision, I_KInput.getMousePos()))
	{
		m_bNextSceneStart = true;
	}
	return true;
}
bool EndScene::Render()
{
	m_BackGround.Render();
	m_btnStart.Render();
	return true;
}
bool EndScene::Release()
{
	m_BackGround.Release();
	m_btnStart.Release();
	return true;
}
bool EndScene::Reset()
{
	return true;
}
EndScene::EndScene() : Scene(3)
{
}
EndScene::~EndScene()
{
}
