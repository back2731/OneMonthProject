#pragma once
#include "GameNode.h"
#include "MapToolTile.h"



enum Select
{
	SELECT_START,
	SELECT_END,
	SELECT_BLOCK
};
enum Direction 
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFTUP,
	DIRECTION_RIGHTDOWN,
	DIRECTION_LEFTDOWN,
	DIRECTION_RIGHTUP
};

struct tagTile 
{
	RECT rc;
	bool block;

	int node;

	int showState;

	int f, g, h;
};

enum State
{
	STATE_NONE,
	STATE_OPEN,
	STATE_CLOSE,
	STATE_PATH
};

class aStarScene :public GameNode
{
private:

	tagTile tiles[TILESIZE];

	vector<int> openList;
	vector<int>closeList;
	vector<int>::iterator iter;
	TagTile _tileMap[TILE_COUNT_X][TILE_COUNT_Y];


	Select currentSelect;

	int startTile;
	int endTile;
	int currentTile;
	bool isFind;
	bool noPath;
	bool startAstar;

	bool isArrive;

	RECT rc[6];

	RECT playerRect;
	int playerStart;


	int endX;
	int endY;
	int count;

	HBRUSH brush;
	HFONT font,oldFont;
	char str[128];
	int temp;
	const char* fileName[10] = { "map1.map","map2.map","map3.map","map4.map","map5.map","map6.map","map7.map","map8.map","map9.map","map10.map" };

	HANDLE file;
	DWORD write;
	DWORD read;

	int currentX;
	int currentY;

	RECT cameraRect = { 0,0,WINSIZEX,WINSIZEY };
	RECT tempRect;
	
public:
	aStarScene();
	~aStarScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void Astar();

	void Load(int loadCount);

};

