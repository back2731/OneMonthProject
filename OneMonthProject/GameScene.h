#pragma once
#include "GameNode.h"
#include "MainMap.h"

#include "Hatchery.h"

class GameScene : public GameNode
{
private:
	MainMap* mainMap;

public:
	GameScene();
	~GameScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

private:
	vector<BuildBase*> m_MyBuilding;
};

