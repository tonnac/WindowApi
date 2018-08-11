#include "Core.h"


bool Core::GameInit()
{
	Init();
	return true;
}
bool Core::GameFrame()
{
	Frame();
	return true;
}
bool Core::GameRender()
{
	Render();
	return true;
}
bool Core::GameRelease()
{
	Release();
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
Core::Core(HINSTANCE a, LONG b, LONG c) : Window(a, b, c)
{}