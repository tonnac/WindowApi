#include "Core.h"


bool Core::Init()
{
	m_Timer.Init();
	return true;
}
bool Core::Frame()
{
	m_Timer.Frame();
	return true;
}
bool Core::Render()
{
	m_Timer.Render();
	return true;
}
bool Core::Release()
{
	m_Timer.Release();
	return true;
}