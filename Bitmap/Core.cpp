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
	GameRedner();
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
	m_Timer.Frame();
	I_Input.Frame();
	Frame();
	return true;
}
bool Core::GameRedner()
{
	Render();
	m_Timer.Render();
//	I_Input.Render();
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