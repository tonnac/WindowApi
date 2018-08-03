#pragma once
#include "WindowClass.h"
#include "Timer.h"
#include "Input.h"

class Core : public Window
{
public:
	bool				GameInit() override;
	bool				GameRun() override;
	bool				GameRelease() override;
public:
	bool				GameFrame();
	bool				GameRedner();
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
public:
	Timer m_Timer;
};