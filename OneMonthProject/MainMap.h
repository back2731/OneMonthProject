#pragma once
#include"MapToolTile.h"

class MainMap
{
private:
	TAGTILE _tileMap[TILE_COUNT_X*TILE_COUNT_Y];

	int _locationX, _locationY;
	int _center;
	char str[128];

	//int count = 0;

	int loadData;
	int resetData;

	int currentX;
	int currentY;

	RECT cameraRect;
	RECT temp;

	//
	const char* fileName[10] = { "map1.map","map2.map","map3.map","map4.map","map5.map","map6.map","map7.map","map8.map","map9.map","map10.map" };
	HANDLE file;
	DWORD write;
	DWORD read;

public:
	MainMap();
	~MainMap();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void DrawTileMap(HDC hdc);
	void Load(int loadCount);

	void DrawLineX(HDC hdc, int left, int top);
	void DrawLineY(HDC hdc, int left, int top);

	//DWORD* getAttribute() { return _attribute; }
	//tagTile* getMap() { return _map; }
	//int getPosFirst() { return _pos[0]; }
	//int getPosSecond() { return _pos[1]; }
	//void attackBlock(int tileN);
};

