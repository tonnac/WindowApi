#pragma once
#include "Core.h"
#include "NPC.h"
#include "BitmapMgr.h"
#include "BKObject.h"
#include "Collision.h"
#include "Button.h"
#include "Player.h"

class Sample;

class Scene
{
public:
	Scene(SCENE, Sample*);
public:
	virtual	bool			Init() = 0;
	virtual	bool			Frame() = 0;
	virtual	bool			Render() = 0;
	virtual	bool			Release() = 0;
public:
	void * operator new(size_t sz, const char* FileName, int iLine);
	void operator delete(void * p);
public:
protected:
	Sample *				_Sample;
	bool					isNextScene;
	SCENE					SceneID;
	BKObject				bkobj;
};


class LobbyScene : public Scene
{
public:
	LobbyScene(Sample*);
	bool					Init() override;
	bool					Frame() override;
	bool					Render() override;
	bool					Release() override;
public:
private:
	Button					m_startButton;
};
class GameScene : public Scene
{
	Player  _Player;
	NPC		n1[10];
	const int iNPc;
public:
	GameScene(Sample*);
	bool					Init() override;
	bool					Frame() override;
	bool					Render() override;
	bool					Release() override;
private:

};
class EndScene : public Scene
{
public:
	EndScene(Sample*);
	bool					Init() override;
	bool					Frame() override;
	bool					Render() override;
	bool					Release() override;
public:
private:
	Button					m_EndButton;

};