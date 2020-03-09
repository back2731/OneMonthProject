#pragma once
#include"GameNode.h"
#include"MapToolTile.h"

class SubMap : public GameNode
{
private:

	bool isDebug;

	int currentTile;
	RECT rc[TILE_SIZE_X][TILE_SIZE_Y];

	int frameX, frameY;

public:
	SubMap();
	~SubMap();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};