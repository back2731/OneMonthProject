#pragma once
#include "GameNode.h"
#include "MapToolTile.h"

#define SPEED 5
#define SPEED2 3


//크기
#define CELL_WIDTH	64
#define CELL_HEIGHT 64

//타일 갯수
#define TILE_COUNT_X 64
#define TILE_COUNT_Y 64

//타일 이미지
#define TILE_SIZE_X 16
#define TILE_SIZE_Y 17

#define TILE_MAX 1

#define TILEX 64
#define TILEY 64
#define TILESIZE TILEX*TILEY

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

	vector<int> saveRoad;

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
	RECT testRect[TILESIZE];

	int endX;
	int endY;
	int count;

	int playerX;
	int playerY;


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

	RECT cameraRect;
	RECT tempRect;
	
public:
	aStarScene();
	~aStarScene();

	HRESULT Init(float unitX, float unitY);
	void Release();
	void Update(float unitX, float unitY);
	void Render();

	void Astar();

	void Load(int loadCount);

	float GetUnitX() { return playerX; }
	float GetUnitY() { return playerY; }

};

