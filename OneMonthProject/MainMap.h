#pragma once
#include"GameNode.h"
#include"MapToolTile.h"
class MainMap : public GameNode
{
private:
	TagTile _tileMap[TILE_COUNT_X][TILE_COUNT_Y];

	int _locationX, _locationY;
	int _center;
	char str[128];

	int count = 0;

	int loadData;
	int resetData;

	int currentX;
	int currentY;

	int savePositionX;
	int savePositionY;
	
	POINT imageFrame;
	CTRL _currentCTRL;
	RECT cameraRect;
	RECT temp;

	Image* miniMapBoardImage;
	RECT miniMapBoardRect;

	Image* currentPositionImage;
	RECT currentPositionRect[5][5];

	Image* passedPositionImage;
	RECT passedPositionRect[5][5];

	bool _isDebug;

	bool openDoor;
	bool stopCamera;

	bool moveUp;
	bool moveDown;
	bool moveRight;
	bool moveLeft;
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
	void Render();

	void DrawTileMap();
	void load(int loadCount);

	void DrawLineX(int left, int top);
	void DrawLineY(int left, int top);

	//DWORD* getAttribute() { return _attribute; }
	//tagTile* getMap() { return _map; }
	//int getPosFirst() { return _pos[0]; }
	//int getPosSecond() { return _pos[1]; }
	//void attackBlock(int tileN);
};

