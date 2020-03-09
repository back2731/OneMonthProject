#include "stdafx.h"
#include "MainMap.h"

MainMap::MainMap()
{
}

MainMap::~MainMap()
{
}

HRESULT MainMap::Init()
{
	return S_OK;
}

void MainMap::Release()
{
}

void MainMap::Update()
{

}

void MainMap::Render()
{
}

void MainMap::DrawTileMap()
{

}

void MainMap::load(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}

void MainMap::Draw_Line_X(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(GetMemDC(), centerX, centerY, centerX + CELL_WIDTH, centerY);
}

void MainMap::Draw_Line_Y(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(GetMemDC(), centerX, centerY, centerX, centerY + CELL_HEIGHT);
}
