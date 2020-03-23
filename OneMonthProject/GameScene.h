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
	
	TAGTILE _tileMap[TILE_COUNT_X*TILE_COUNT_Y];
	

	RECT dragRect;
	RECT tempRect;
	RECT cameraRect;
	RECT commandRect;

	int count;
	char str[128];

	float leftPoint;
	float topPoint;
	float rightPoint;
	float bottomPoint;

	const char*		fileName[10] = { "map1.map","map2.map","map3.map","map4.map","map5.map","map6.map","map7.map","map8.map","map9.map","map10.map" };

	HANDLE			file;
	DWORD			write;
	DWORD			read;

	POINT			start;
	POINT			end;
public:
	GameScene();
	~GameScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void LoadMap(int loadCount);

	//void SetUnitVector(UnitBase* UnitClass) { unitVector.push_back(UnitClass); }

};

