#pragma once
#include "GameNode.h"

class GameScene : public GameNode
{
private:
	vector<BuildBase*>	buildingVector;
	vector<UnitBase*>	unitVector;
	vector<UnitBase*>	airUnitVector;
	vector<UnitBase*>	selectVector;
	
	vector<BuildBase*>	enemyBuildingVector;
	vector<UnitBase*>	enemyUnitVector;

	TAGTILE				_tileMap[TILE_COUNT_X*TILE_COUNT_Y];
	
	Image*				consoleImage;
	Image*				portraitsBorder;

	RECT				dragRect;
	RECT				tempRect;
	RECT				cameraRect1;
	RECT				cameraRect2;
	RECT				commandRect;

	RECT				gas;

	int					count;
	char				str[128];

	float				leftPoint;
	float				topPoint;
	float				rightPoint;
	float				bottomPoint;

	const char*			fileName[10] = { "map1.map","map2.map","map3.map","map4.map","map5.map","map6.map","map7.map","map8.map","map9.map","map10.map" };

	HANDLE				file;
	DWORD				write;
	DWORD				read;

	Image*				mineralImage;
	Image*				vespeneGasImage;
	Image*				populationImage;
	float				mineral;
	float				vespeneGas;
	float				currentPopulation;
	float				maxPopulation;
	
	bool				searching;

public:
	GameScene();
	~GameScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void LoadMap(int loadCount);
	void DrawTileMap();
};

