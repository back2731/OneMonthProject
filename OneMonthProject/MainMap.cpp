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
	_isDebug = false;

	return S_OK;
}

void MainMap::Release()
{
}

void MainMap::Update()
{
	cameraRect = RectMake(CAMERAMANAGER->GetCameraXY().x - WINSIZEX, CAMERAMANAGER->GetCameraXY().y - WINSIZEY, WINSIZEX * 2, WINSIZEY * 2);
}

void MainMap::Render()
{
	DrawTileMap();
	//Rectangle(GetMemDC(), cameraRect.left, cameraRect.top, cameraRect.right, cameraRect.bottom);
	//HBRUSH brush = CreateSolidBrush(RGB(0, 102, 0));
	//FillRect(GetMemDC(), &cameraRect, brush);
	//DeleteObject(brush);
	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILE_COUNT_X; i++)
		{
			for (int j = 0; j < TILE_COUNT_Y; j++)
			{
				if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
				{
					SetTextColor(GetMemDC(), RGB(255, 0, 0));
					sprintf_s(str, "(%d,%d)", i, j);
					TextOut(GetMemDC(), _tileMap[i][j].left + CELL_WIDTH / 2 - 20, _tileMap[i][j].top + CELL_HEIGHT / 2 - 10, str, strlen(str));
				}
			}
		}
	}
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

			if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
			{
				if (_tileMap[i][j].tileKind != TILEKIND_NONE)
				{
					switch (_tileMap[i][j].tileKind)
					{
					case TILEKIND_TERRAIN:
						IMAGEMANAGER->FrameRender("BaseMap", GetMemDC(),
							_tileMap[i][j].left, _tileMap[i][j].top, _tileMap[i][j].tilePos.x, _tileMap[i][j].tilePos.y);
							break;
					case TILEKIND_TERRAIN2:
						IMAGEMANAGER->FrameRender("MapTile1", GetMemDC(),
							_tileMap[i][j].left, _tileMap[i][j].top, _tileMap[i][j].tilePos.x, _tileMap[i][j].tilePos.y);
						break;
					case TILEKIND_TERRAIN3:
						IMAGEMANAGER->FrameRender("MapTile2", GetMemDC(),
							_tileMap[i][j].left, _tileMap[i][j].top, _tileMap[i][j].tilePos.x, _tileMap[i][j].tilePos.y);
						break;
					}
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

void MainMap::DrawLineX(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(GetMemDC(), centerX, centerY, centerX + CELL_WIDTH, centerY);
}

void MainMap::DrawLineY(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(GetMemDC(), centerX, centerY, centerX, centerY + CELL_HEIGHT);
}
