#pragma once
#include "WindowClass.h"
#include "Timer.h"
#include "Input.h"

class Core : public Window
{
public:
	bool					GameInit() override;
	bool					GameRun() override;
	bool					GameRelease() override;
private:
	bool					GameFrame();
	bool					GameRender();
private:
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Render();
	virtual bool			Release();
private:
	Timer					m_Timer;
};