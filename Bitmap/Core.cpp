#include "Core.h"

bool Core::GameInit()
{
	m_Timer.Init();
	I_Input.Init();
	Init();
	return true;
}
bool Core::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
bool Core::GameRelease()
{
	Release();
	m_Timer.Release();
	I_Input.Release();
	return true;
}
bool Core::GameFrame()
{
	Frame();
	m_Timer.Frame();
	I_Input.Frame();
	return true;
}
bool Core::GameRender()
{
	m_Timer.Render();
	I_Input.Render();
	Render();
	return true;
}

bool Core::Init()
{
	return true;
}
bool Core::Frame()
{
	return true;
}
bool Core::Render()
{
	return true;
}
bool Core::Release()
{
	return true;
}