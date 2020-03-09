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
			rc[i][j] = RectMake(CELL_WIDTH / 2 * i, CELL_HEIGHT / 2 * j + 200, CELL_WIDTH / 2, CELL_HEIGHT / 2);
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
		for (int i = 0; i < TILE_SIZE_X; i++)
		{
			for (int j = 0; j < TILE_SIZE_Y; j++)
			{
				if (PtInRect(&rc[i][j], SUBWIN->GetMousePos()))
				{
					SUBWIN->SetFramePoint(PointMake(i, j));
				}
			}
		}
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_SHIFT))
	{
		isDebug = !isDebug;
	}
}

void SubMap::Render(HDC hdc)
{
	switch (SUBWIN->GetFrameIndex())
	{
	case CTRL_NUM1:
		for (int i = 0; i < TILE_SIZE_X; i++)
		{
			for (int j = 0; j < TILE_SIZE_Y; j++)
			{
				IMAGEMANAGER->FindImage("blocks")->FrameRender(hdc, CELL_WIDTH / 2 * i, CELL_HEIGHT / 2 * j + 200, i, j, CELL_WIDTH / 2, CELL_HEIGHT / 2);
			}
		}//end of for
		break;
	case CTRL_NUM2:
		for (int i = 0; i < TILE_SIZE_X; i++)
		{
			for (int j = 0; j < TILE_SIZE_Y; j++)
			{
				IMAGEMANAGER->FindImage("blocks")->FrameRender(hdc, CELL_WIDTH / 2 * i, CELL_HEIGHT / 2 * j + 200, i, j, CELL_WIDTH / 2, CELL_HEIGHT / 2);
			}
		}//end of for
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