#include "Core.h"
#include "Scene.h"
#include "GameScene.h"

class Sample : public Core
{
public:
	Sample()
	{
		s1 = New LobbyScene;
		s2 = New GameScene;
		CurrentScene = nullptr;
	}
public:
	bool Init()
	{
		s1->Init();
		s2->Init();
		CurrentScene = s2;
		return true;
	}
	bool Frame()
	{
		if (CurrentScene->getNextScene())
		{
			CurrentScene = s2;
		}
		CurrentScene->Frame();
		return true;
	}
	bool Render()
	{
		CurrentScene->Render();
		return true;
	}
	bool Release()
	{
		s1->Release();
		s2->Release();
		delete s1;
		delete s2;
		return true;
	}
private:
	LobbyScene* s1;
	GameScene* s2;
	Scene * CurrentScene;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 960, 720);
	wd.Run();

	return 0;
}