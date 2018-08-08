#include "Scene.h"
#include <memory>

class KSample : public KCore
{
public:
	int							m_iLevel;
	std::shared_ptr<Scene>		m_pGameScene;
	std::shared_ptr<Scene>		m_pLobbyScene;
	std::shared_ptr<Scene>		m_pEndScene;
	Scene *						m_pCurrentScene;
public:
	bool Init()
	{
		m_iLevel = 1;
		m_pGameScene = std::make_shared<GameScene>();
		m_pLobbyScene = std::make_shared<LobbyScene>();
		m_pEndScene = std::make_shared<EndScene>();
		m_pCurrentScene = m_pLobbyScene.get();
		
		m_pGameScene->Init();
		m_pLobbyScene->Init();
		m_pEndScene->Init();

		m_pCurrentScene->Init();

		return true;
	}
	bool Frame()
	{
		m_pCurrentScene->Frame();
		switch (m_pCurrentScene->m_iSceneID)
		{
		case 1:
			if (m_pCurrentScene->m_bNextSceneStart)
			{
				m_pCurrentScene = m_pGameScene.get();
			}
			break;
		case 2:
			if (m_pCurrentScene->m_bNextSceneStart)
			{
				if (m_iLevel + 1 > g_iMaxNpcCount / 10)
				{
					m_iLevel = 0;
					m_pCurrentScene = m_pEndScene.get();
				}
				m_pCurrentScene->m_iMaxNpcCount = ++m_iLevel * 10;
				m_pCurrentScene->Reset();
				
			}
			break;
		case 3:
			if (m_pCurrentScene->m_bNextSceneStart)
			{
				DestroyWindow(g_hWnd);
			}
			break;
		}
		return true;
	}
	bool Render()
	{
		m_pCurrentScene->Render();
		return true;
	}
	bool Release()
	{
		m_pGameScene->Release();
		m_pLobbyScene->Release();
		m_pEndScene->Release();
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