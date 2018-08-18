#include "GameScene.h"
#include "Rendering.h"

GameScene::GameScene() : m_pScroll(&m_pPlayer,&m_BKObject), m_pFadeObject(nullptr)
{}
bool GameScene::Init()
{
	m_pFadeObject = New FadeObject;
	m_pFadeObject->Set(0,0,0,0,g_rtClient.right,g_rtClient.bottom);
	m_pFadeObject->Init();

	S_SpriteMgr.SpriteSet(L"../02_data/txt/Kaho.txt");
	m_pPlayer.LoadFile(L"PLAYER", L"../02_data/bmp/KahoColor.bmp", L"../02_data/bmp/KahoMask.bmp");
	m_BKObject.LoadFile(L"BACKGROUND", L"../02_data/bmp/Map.bmp");
	m_BKObject.Set(0, 0, 0, 0, 2072, 772);
	m_BKObject.Init();

	TerrainObject * t1 = New TerrainObject;
	t1->Set(0, 622, 0, 622, 1560, 150);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1560, 568, 1560, 568, 103, 204);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1663, 468, 1663, 468, 155, 304);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1818, 623, 1818, 623, 335, 151);
	m_BKObject.AddTerrain(t1);

	m_pPlayer.Set(130, 580, 10, 87, 25, 36);
	m_pPlayer.Init();
	m_pPlayer.setRendering(2.8f, INVERSE::DEFAULT);

	m_pScroll.Init();

	return true;
}
bool GameScene::Frame()
{
	if (m_BKObject.Collision(&m_pPlayer) == false)
	{
		m_BKObject.setRendering();
	}
	m_pPlayer.Frame();
	m_pScroll.Frame();
	if (m_pFadeObject)
	{
		if (!m_pFadeObject->Frame())
		{
			delete m_pFadeObject;
			m_pFadeObject = nullptr;
		}
	}

	return true;
}
bool GameScene::Render()
{
	m_BKObject.Render();
	m_pPlayer.Render();
	m_pScroll.Render();
	if (m_pFadeObject)
	{
		m_pFadeObject->Render();
	}
	return true;
}
bool GameScene::Release()
{
	m_pPlayer.Release();
	m_BKObject.Release();
	return true;
}