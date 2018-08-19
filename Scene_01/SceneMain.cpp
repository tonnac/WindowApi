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
		s3 = New GameScene2;
		CurrentScene = nullptr;
	}
public:
	bool Init()
	{
		s1->Init();
		s2->Init();
		s3->Init();
		CurrentScene = s3;
		return true;
	}
	bool Frame()
	{
		if (CurrentScene->getNextScene())
		{
			s2->inverseset();
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
		s3->Release();
		delete s1;
		delete s2;
		delete s3;
		return true;
	}
private:
	LobbyScene* s1;
	GameScene* s2;
	GameScene2* s3;
	Scene * CurrentScene;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 960, 720);
	wd.Run();

	return 0;
}