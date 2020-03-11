#pragma once
#include "GameNode.h"
#include "MapToolTile.h"
#include "SubMap.h"

#define SUBWINOPEN 1

class MapToolScene : public GameNode
{
private:
	SubMap* sub = new SubMap;

	TagTile _tileMap[TILE_COUNT_X][TILE_COUNT_Y];

	int _locationX, _locationY;
	int _center;
	char str[128];


	int currentX;
	int currentY;

	bool openDoor;

	POINT imageFrame;
	CTRL _currentCTRL;
	RECT cameraRect = { -WINSIZEX,-WINSIZEY,WINSIZEX*2,WINSIZEY*2 };
	RECT debugRect = { 0,0,WINSIZEX,WINSIZEY };
	RECT temp;

	bool _isDebug;

	//
	const char* fileName[10] = { "map1.map","map2.map","map3.map","map4.map","map5.map","map6.map","map7.map","map8.map","map9.map","map10.map" };
	HANDLE file;
	DWORD write;
	DWORD read;

public:
	MapToolScene();
	~MapToolScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void SetSubWindow();

	//타일맵 그리자.
	void DrawTileMap();

	//라인 그려주기
	void DrawLineX(int left, int top);
	void DrawLineY(int left, int top);

	void SetMapTool();
	void SetMap(int locationX, int locationY, bool isAdd);
	TILEKIND SelectKind(int frameX, int frameY);

	void TlieInit();
	void Load(int loadCount);
	void Save(int saveCount);
};
