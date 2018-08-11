#pragma once
#include "Scene.h"
class Sample : public Core
{
public:
	Sample();
public:
	void			SetScene(Scene*);
	Scene*			getLobby();
	Scene*			getGame();
	Scene*			getEnd();
public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
private:
	Scene *			_LobbyScene;
	Scene *			_GameScene;
	Scene *			_EndScene;
	Scene *			_CurrentScene;
};