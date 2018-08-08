#pragma once
#include "Core.h"
#include "BkObject.h"
#include "NPCObj.h"
#include "Collision.h"
#include "Button.h"

const int g_iMaxNpcCount = 100;

class Scene
{
public:
	const int						m_iSceneID;
	BkObject						m_BackGround;
	bool							m_bNextSceneStart;
	int								m_iMaxNpcCount;
public:
	virtual bool					Init();
	virtual bool					Frame();
	virtual bool					Render();
	virtual bool					Release();
	virtual bool					Reset();
public:
	Scene(int = 0);
	virtual ~Scene();
private:
};

class LobbyScene : public Scene
{
	Button							m_btnStart;
public:
	virtual bool					Init() override;
	virtual bool					Frame() override;
	virtual bool					Render() override;
	virtual bool					Release() override;
	virtual bool					Reset() override;
public:
	LobbyScene();
	virtual ~LobbyScene();
};

class GameScene : public Scene
{
	std::vector<NPCObj>				m_npcList;
	Object							m_Hero;
public:
	virtual bool					Init() override;
	virtual bool					Frame() override;
	virtual bool					Render() override;
	virtual bool					Release() override;
	virtual bool					Reset() override;
public:
	GameScene();
	virtual ~GameScene();
};

class EndScene : public Scene
{
	Button							m_btnStart;
public:
	virtual bool					Init() override;
	virtual bool					Frame() override;
	virtual bool					Render() override;
	virtual bool					Release() override;
	virtual bool					Reset() override;
public:
	EndScene();
	virtual ~EndScene();
};