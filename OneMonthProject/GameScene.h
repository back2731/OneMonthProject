#pragma once
#include "GameNode.h"
#include "MainMap.h"

class GameScene : public GameNode
{
private:
	MainMap* mainMap;
	Image* test1;
	Animation* testAni;
	RECT testRect;

public:
	GameScene();
	~GameScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

