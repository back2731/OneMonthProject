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

	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 102, 0));
		for (int i = 0; i < TILESIZE; i++)
		{
			if (IntersectRect(&temp, &cameraRect, &_tileMap[i].rect))
			{
				if (_tileMap[i].block == true)
				{
					Rectangle(hdc, _tileMap[i].rect.left, _tileMap[i].rect.top, _tileMap[i].rect.right, _tileMap[i].rect.bottom);
					FillRect(hdc, &_tileMap[i].rect, brush);
				}

				SetTextColor(hdc, RGB(255, 0, 0));
				sprintf_s(str, "(%d)", i);
				TextOut(hdc, _tileMap[i].left + CELL_WIDTH / 2 - 20, _tileMap[i].top + CELL_HEIGHT / 2 - 10, str, strlen(str));
			}
		}
		DeleteObject(brush);
	}
}

void MainMap::DrawTileMap(HDC hdc)
{
	for (int i = 0; i < TILESIZE; i++)
	{
		if (IntersectRect(&temp, &cameraRect, &_tileMap[i].rect))
		{
			if (_tileMap[i].tileKind != TILEKIND_NONE)
			{
				switch (_tileMap[i].tileKind)
				{
				case TILEKIND_BASETERRAIN:
					IMAGEMANAGER->FrameRender("BaseMap", hdc, _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
						break;
				case TILEKIND_TERRAIN:
					IMAGEMANAGER->FrameRender("MapTile1", hdc, _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_CREEP:
					IMAGEMANAGER->FrameRender("MapTile1", hdc, _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_STAIR:
					IMAGEMANAGER->FrameRender("MapTile2", hdc, _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_STAIRBLOCK:
					IMAGEMANAGER->FrameRender("MapTile2", hdc, _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
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
