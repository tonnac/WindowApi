#include "Scene.h"
#include "Sample.h"

Scene::Scene(SCENE _SceneID, Sample* sample) : SceneID(_SceneID), isNextScene(false), _Sample(sample)
{}
void * Scene::operator new(size_t sz, const char* FileName, int iLine)
{
	MEMINFO mem;
	void* pfs = new char[sz];
	mem.addr = pfs;
	mem.filename = FileName;
	mem.line = iLine;
	mem.dwAllocateTime = timeGetTime();
	MemoryMap.insert(std::make_pair(pfs, mem));
	++::g_iNewCount;
	return pfs;
}
void Scene::operator delete(void * p)
{
	std::map<void*, MEMINFO>::iterator it;
	it = MemoryMap.find(p);
	MemoryMap.erase(it);
	--::g_iNewCount;
	delete p;
}



LobbyScene::LobbyScene(Sample* sample) : Scene(SCENE::LOBBY, sample)
{}

bool LobbyScene::Init()
{
	bkobj.Init();
	bkobj.LoadFile(L"BACKGROUND", L"../02_data/bk.bmp");
	bkobj.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);

	m_startButton.Init();
	m_startButton.LoadFile(L"BUTTON", L"../02_data/main_start_nor.bmp");
	m_startButton.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 334, 82);
	return true;
}
bool LobbyScene::Frame()
{
	RECT rt = m_startButton.getCollisionRt();
	POINT mouse = S_Input.GetMousePos();
	bkobj.Frame();
	m_startButton.Frame();
	if (Collision::RectInPt(rt, mouse) && S_Input.GetMouse(VK_LBUTTON) == KEYSTATE::KEY_PUSH)
	{
		_Sample->SetScene(_Sample->getGame());
	}
	return true;
}
bool LobbyScene::Render()
{
	bkobj.Render();
	m_startButton.Render();
	return true;
}
bool LobbyScene::Release()
{
	bkobj.Frame();
	m_startButton.Release();
	return true;
}

GameScene::GameScene(Sample* sample) : Scene(SCENE::GAME, sample), iNPc(10)
{}
bool GameScene::Init()
{
	for (int i = 0; i < iNPc; i++)
	{
		n1[i].Init();
		n1[i].LoadFile(L"NPC", L"../02_data/bitmap1.bmp", L"../02_data/bitmap2.bmp");
		n1[i].Set(rand() % 100 + 200, rand() % 100 + 200, 115, 62, 36, 35);
	}
	bkobj.Init();
	bkobj.LoadFile(L"BACKGROUND", L"../02_data/bk.bmp");
	bkobj.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);
	_Player.Init();

	return true;
}
bool GameScene::Frame()
{
	POINT mpos = S_Input.GetMousePos();

	bkobj.Frame();
	_Player.Frame();

	for (int i = 0; i < iNPc; i++)
	{
		RECT n_rt = n1[i].getCollisionRt();
		if (Collision::RectInPt(n_rt, mpos) && S_Input.GetMouse(VK_LBUTTON) == KEYSTATE::KEY_PUSH)
		{
			n1[i].isDead = true;
		}
		n1[i].Frame();
	}
	return true;
}
bool GameScene::Render()
{
	bkobj.Render();
	_Player.Render();

	bool end = true;
	for (int i = 0; i < iNPc; i++)
	{
		if (!n1[i].isDead)
		{
			n1[i].Render();
			end = false;
		}
	}
	if (end)
	{
		_Sample->SetScene(_Sample->getEnd());
	}
	return true;
}
bool GameScene::Release()
{
	bkobj.Release();
	_Player.Release();
	for (int i = 0; i < iNPc; i++)
	{
		n1[i].Release();
	}
	return true;
}


EndScene::EndScene(Sample * sample) : Scene(SCENE::END, sample)
{}
bool EndScene::Init()
{
	bkobj.Init();
	bkobj.LoadFile(L"ENDBACK",L"../02_data/RAINBOW.bmp");
	bkobj.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_EndButton.Init();
	m_EndButton.LoadFile(L"ENDBUTTON",L"../02_data/end.bmp");
	m_EndButton.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 100, 50);
	return true;
}
bool EndScene::Frame()
{
	RECT rt = m_EndButton.getCollisionRt();
	POINT mPos = S_Input.GetMousePos();
	bkobj.Frame();
	m_EndButton.Frame();
	
	if (Collision::RectInPt(rt, mPos) && S_Input.GetMouse(VK_LBUTTON) == KEYSTATE::KEY_UP)
	{
		DestroyWindow(g_hWnd);
	}
	return true;
}
bool EndScene::Render()
{
	bkobj.Render();
	m_EndButton.Render();
	return true;
}
bool EndScene::Release()
{
	bkobj.Release();
	m_EndButton.Release();
	return true;
}