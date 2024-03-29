#pragma once
#include "WindowClass.h"
#include "Timer.h"

class Core : public Window
{
public:
	bool	GameInit();
	bool	GameRun();
	bool	GameRelease();
private:
	bool	GameFrame();
	bool	GameRender();
private:
	Timer m_Timer;
};