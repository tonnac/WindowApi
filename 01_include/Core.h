#pragma once
#include "WindowClass.h"
#include "Timer.h"
#include "Input.h"
#include "Bitmap.h"

class Core : public Window
{
public:
	bool					GameInit() override;
	bool					GameRun() override;
	bool					GameRelease() override;
private:
	bool					GameFrame();
	bool					GameRender();
	bool					GamePreRender();
	bool					GamePostRender();
private:
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Render();
	virtual bool			Release();
private:
//	HDC						m_hOffScreenDC;
	HDC						m_hScreenDC;
	HBITMAP					m_hOffBitmap;
	HBRUSH					m_hBkbrush;
private:
	Timer					m_Timer;
};