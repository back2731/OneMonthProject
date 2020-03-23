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

	Load(0);

	return S_OK;
}

void MainMap::Release()
{
}

void MainMap::Update()
{
	cameraRect = RectMake(CAMERAMANAGER->GetCameraXY().x - WINSIZEX, CAMERAMANAGER->GetCameraXY().y - WINSIZEY, WINSIZEX * 2, WINSIZEY * 2);
}

void MainMap::Render(HDC hdc)
{
	DrawTileMap(hdc);
	//Rectangle(hdc, cameraRect.left, cameraRect.top, cameraRect.right, cameraRect.bottom);
	//HBRUSH brush = CreateSolidBrush(RGB(0, 102, 0));
	//FillRect(hdc, &cameraRect, brush);
	//DeleteObject(brush);
	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILE_COUNT_X; i++)
		{
			for (int j = 0; j < TILE_COUNT_Y; j++)
			{
				if (IntersectRect(&temp, &cameraRect, &_tileMap[i*TILE_COUNT_X+j].rect))
				{
					SetTextColor(hdc, RGB(255, 0, 0));
					sprintf_s(str, "(%d)", i*TILE_COUNT_X + j);
					TextOut(hdc, _tileMap[i*TILE_COUNT_X+j].left + CELL_WIDTH / 2 - 20, _tileMap[i*TILE_COUNT_X+j].top + CELL_HEIGHT / 2 - 10, str, strlen(str));
				}
			}
		}
	}

	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 102, 0));
		for (int i = 0; i < TILESIZE; i++)
		{
			if (_tileMap[i].block == true)
			{
				Rectangle(hdc, _tileMap[i].rect.left, _tileMap[i].rect.top, _tileMap[i].rect.right, _tileMap[i].rect.bottom);
				FillRect(hdc, &_tileMap[i].rect, brush);
			}
		}
		DeleteObject(brush);
	}
}

void MainMap::DrawTileMap(HDC hdc)
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			int left = currentX + (i * CELL_WIDTH);
			int top = currentY + (j * CELL_HEIGHT);
			int right = currentX + (i * CELL_WIDTH) + CELL_WIDTH;
			int bottom = currentY + (j * CELL_HEIGHT) + CELL_HEIGHT;

			_tileMap[i*TILE_COUNT_X+j].left = left;
			_tileMap[i*TILE_COUNT_X+j].top = top;
			_tileMap[i*TILE_COUNT_X+j].right = right;
			_tileMap[i*TILE_COUNT_X+j].bottom = bottom;
			_tileMap[i*TILE_COUNT_X+j].rect = { _tileMap[i*TILE_COUNT_X+j].left , _tileMap[i*TILE_COUNT_X+j].top , _tileMap[i*TILE_COUNT_X+j].right , _tileMap[i*TILE_COUNT_X+j].bottom };

			if (IntersectRect(&temp, &cameraRect, &_tileMap[i*TILE_COUNT_X+j].rect))
			{
				if (_tileMap[i*TILE_COUNT_X+j].tileKind != TILEKIND_NONE)
				{
					switch (_tileMap[i*TILE_COUNT_X+j].tileKind)
					{
					case TILEKIND_BASETERRAIN:
						IMAGEMANAGER->FrameRender("BaseMap", hdc,
							_tileMap[i*TILE_COUNT_X+j].left, _tileMap[i*TILE_COUNT_X+j].top, _tileMap[i*TILE_COUNT_X+j].tilePos.x, _tileMap[i*TILE_COUNT_X+j].tilePos.y);
							break;
					case TILEKIND_TERRAIN:
						IMAGEMANAGER->FrameRender("MapTile1", hdc,
							_tileMap[i*TILE_COUNT_X+j].left, _tileMap[i*TILE_COUNT_X+j].top, _tileMap[i*TILE_COUNT_X+j].tilePos.x, _tileMap[i*TILE_COUNT_X+j].tilePos.y);
						break;
					case TILEKIND_CREEP:
						IMAGEMANAGER->FrameRender("MapTile1", hdc,
							_tileMap[i*TILE_COUNT_X + j].left, _tileMap[i*TILE_COUNT_X + j].top, _tileMap[i*TILE_COUNT_X + j].tilePos.x, _tileMap[i*TILE_COUNT_X + j].tilePos.y);
						break;
					case TILEKIND_STAIR:
						IMAGEMANAGER->FrameRender("MapTile2", hdc,
							_tileMap[i*TILE_COUNT_X+j].left, _tileMap[i*TILE_COUNT_X+j].top, _tileMap[i*TILE_COUNT_X+j].tilePos.x, _tileMap[i*TILE_COUNT_X+j].tilePos.y);
						break;
					case TILEKIND_STAIRBLOCK:
						IMAGEMANAGER->FrameRender("MapTile2", hdc,
							_tileMap[i*TILE_COUNT_X + j].left, _tileMap[i*TILE_COUNT_X + j].top, _tileMap[i*TILE_COUNT_X + j].tilePos.x, _tileMap[i*TILE_COUNT_X + j].tilePos.y);
						break;
					}
				}
			}
		}
	}
}

void MainMap::Load(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TAGTILE) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}

void MainMap::DrawLineX(HDC hdc, int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(hdc, centerX, centerY, centerX + CELL_WIDTH, centerY);
}

void MainMap::DrawLineY(HDC hdc, int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(hdc, centerX, centerY, centerX, centerY + CELL_HEIGHT);
}
