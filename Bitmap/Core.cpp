#include "Core.h"

bool Core::GameInit()
{
	m_Timer.Init();
	m_Input.Init();
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
	m_Input.Release();
	return true;
}
bool Core::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();
	Frame();
	return true;
}
bool Core::GameRender()
{
	Render();
	m_Timer.Render();
	m_Input.Render();
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