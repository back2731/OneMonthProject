#pragma once
#include "GameNode.h"
#include "MainMap.h"

class GameScene : public GameNode
{
private:
	MainMap* mainMap;
	vector<BuildBase*> buildingVector;
	vector<UnitBase*> unitVector;
	vector<UnitBase*> selectVector;

	RECT dragRect;
	RECT tempRect;

	int count;
	char str[128];

	float leftPoint;
	float topPoint;
	float rightPoint;
	float bottomPoint;

public:
	GameScene();
	~GameScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void SetUnitVector(UnitBase* UnitClass) { unitVector.push_back(UnitClass); }

};

