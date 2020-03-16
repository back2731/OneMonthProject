#pragma once
#include "GameNode.h"
#include "MainMap.h"

class GameScene : public GameNode
{
private:
	MainMap* mainMap;
	vector<BuildBase*> buildingVector;
	vector<UnitBase*> unitVector;

	int count;
	char str[128];

public:
	GameScene();
	~GameScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void SetUnitVector(UnitBase* UnitClass) { unitVector.push_back(UnitClass); }

};

