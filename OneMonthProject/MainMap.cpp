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
	_locationX = 0;
	_locationY = 0;
	_center = 0;
	memset(_tileMap, 0, sizeof(_tileMap));

	currentX = 0;
	currentY = 0;

	openDoor = true;

	moveUp = false;
	moveDown = false;
	moveRight = false;
	moveLeft = false;

	stopCamera = true;
	loadData = RND->GetInt(1);
	load(0);

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
	DrawTileMap();
}

void MainMap::DrawTileMap()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			int left = currentX + (i * CELL_WIDTH);
			int top = currentY + (j * CELL_HEIGHT);
			int right = currentX + (i * CELL_WIDTH) + CELL_WIDTH;
			int bottom = currentY + (j * CELL_HEIGHT) + CELL_HEIGHT;

			_tileMap[i][j].left = left;
			_tileMap[i][j].top = top;
			_tileMap[i][j].right = right;
			_tileMap[i][j].bottom = bottom;

			_tileMap[i][j].rect = { _tileMap[i][j].left , _tileMap[i][j].top , _tileMap[i][j].right , _tileMap[i][j].bottom };


			if (_tileMap[i][j].tileKind != TILEKIND_NONE)
			{
				switch (_tileMap[i][j].tileKind)
				{
				case TILEKIND_TERRAIN:
					IMAGEMANAGER->FrameRender("MapTile1", GetMemDC(),
						_tileMap[i][j].left, _tileMap[i][j].top, _tileMap[i][j].tilePos.x, _tileMap[i][j].tilePos.y);
					break;
				case TILEKIND_TERRAIN2:
					IMAGEMANAGER->FrameRender("°è´Ü", GetMemDC(),
						_tileMap[i][j].left, _tileMap[i][j].top, _tileMap[i][j].tilePos.x, _tileMap[i][j].tilePos.y);
					break;
				case TILEKIND_TERRAIN3:
					IMAGEMANAGER->FrameRender("MapTile3", GetMemDC(),
						_tileMap[i][j].left, _tileMap[i][j].top, _tileMap[i][j].tilePos.x, _tileMap[i][j].tilePos.y);
					break;
				}
			}
		}
	}
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
