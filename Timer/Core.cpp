#include "Core.h"

bool Core::GameInit()
{
	m_Timer.Init();
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
	m_Timer.Release();
	return true;
}

bool Core::GameFrame()
{
	m_Timer.Frame();
	return true;
}
bool Core::GameRender()
{
	m_Timer.Render();
	return true;
}