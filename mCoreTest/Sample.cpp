#include "Sample.h"

Sample::Sample()
{

}

void Sample::SetScene(Scene * ChangeScene_)
{
	_CurrentScene = ChangeScene_;
}
Scene* Sample::getLobby()
{
	return _LobbyScene;
}
Scene* Sample::getGame()
{
	return _GameScene;
}
Scene* Sample::getEnd()
{
	return _EndScene;
}

bool Sample::Init()
{
	_LobbyScene = New LobbyScene(this);
	_GameScene = New GameScene(this);
	_EndScene = New EndScene(this);
	_GameScene->Init();
	_LobbyScene->Init();
	_EndScene->Init();
	_CurrentScene = _LobbyScene;
	return true;
}
bool Sample::Frame()
{
	_CurrentScene->Frame();
	return true;
}
bool Sample::Render()
{
	_CurrentScene->Render();
	return true;
}
bool Sample::Release()
{
	_CurrentScene->Release();
	delete _GameScene;
	delete _LobbyScene;
	delete _EndScene;
	return true;
}