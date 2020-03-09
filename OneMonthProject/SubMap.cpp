#include "stdafx.h"
#include "SubMap.h"

SubMap::SubMap()
{
}

SubMap::~SubMap()
{
}

HRESULT SubMap::Init()
{
	for (int i = 0; i < TILE_SIZE_X; i++)
	{
		for (int j = 0; j < TILE_SIZE_Y; j++)
		{
			rc[i][j] = RectMake(SUBWINSIZEX / TILE_SIZE_X * i, 300 / TILE_SIZE_Y * j + 200, SUBWINSIZEX / TILE_SIZE_X, 300 / TILE_SIZE_Y);
		}
	}

	int currentTile = 0;

	isDebug = false;

	return S_OK;
}

void SubMap::Release()
{
}

void SubMap::Update()
{
	if (SUBWIN->GetIsActive() && KEYMANAGER->IsOnceKeyDown(VK_LBUTTON)) // 윈도우활성화 + 왼쪽 클릭 => framepoint 설정.
	{
		for (int i = 0; i < TILE_SIZE_Y; i++)
		{
			for (int j = 0; j < TILE_SIZE_X; j++)
			{
				if (PtInRect(&rc[j][i], SUBWIN->GetMousePos()))
				{
					SUBWIN->SetFramePoint(PointMake(j, i));
				}
			}
		}
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_SHIFT))
		isDebug = !isDebug;
}

void SubMap::Render(HDC hdc)
{
	switch (SUBWIN->GetFrameIndex())
	{
	case CTRL_NUM1:
		for (int i = 0; i < TILE_SIZE_X; i++)
		{
			for (int j = 0; j < TILE_SIZE_Y - 6; j++)
			{
				IMAGEMANAGER->FindImage("mapTile")->FrameRender(hdc, 0 + j * 30, 200 + i * 30, j, i, 30, 30);
			}
		}//end of for
		break;
	case CTRL_NUM2:
		IMAGEMANAGER->FindImage("blocks")->Render(hdc, 0, 200, SUBWINSIZEX, 270);
		break;
	case CTRL_NUM3:
		for (int i = 0; i < TILE_SIZE_X; i++)
		{
			for (int j = 0; j < TILE_SIZE_Y; j++)
			{
				IMAGEMANAGER->FindImage("door")->FrameRender(hdc, 0 + i * 30, 200 + j * 30, i, j, 30, 30);
			}
		}//end of for
		break;
	}//end of switch

	if (isDebug)
	{
		for (int i = 0; i < TILE_SIZE_X; i++)
		{
			for (int j = 0; j < TILE_SIZE_Y; j++)
			{
				RectangleMake(hdc, rc[i][j]);
			}
		}
	}
}