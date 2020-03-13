#pragma once
#include "GameNode.h"
#include "MainMap.h"

#include "Hatchery.h"

class GameScene : public GameNode
{
private:
	MainMap* mainMap;
	vector<BuildBase*> buildingVector;

	int count;
	char str[128];

public:
	GameScene();
	~GameScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

};

