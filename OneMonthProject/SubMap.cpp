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
	//mouseCursor = IMAGEMANAGER->FindImage("Cursor");

	return S_OK;
}

void SubMap::Release()
{
}

void SubMap::Update()
{
	switch (SUBWIN->GetFrameIndex())
	{
	case CTRL_NUM1:
		if (SUBWIN->GetIsActive() && KEYMANAGER->IsOnceKeyDown(VK_LBUTTON)) // 윈도우활성화 + 왼쪽 클릭 => framepoint 설정.
		{
			for (int i = 0; i < TILE_SIZE_X; i++)
			{
				for (int j = 0; j < TILE_SIZE_Y; j++)
				{
					if (PtInRect(&rc[i][j], SUBWIN->GetMousePos()))
					{
						SUBWIN->SetFramePoint(PointMake(0, 0));
					}
				}
			}
		}
		break;
	case CTRL_NUM2:
	case CTRL_NUM3:
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
		break;
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_SHIFT))
	{
		isDebug = !isDebug;
	}
	
	ShowCursor(true);

	//mouseCursor = IMAGEMANAGER->FindImage("Cursor");
	//frameCount++;
	//mouseCursor->SetFrameY(0);
	//if (frameCount % 10 == 0)
	//{
	//	frameCount = 0;
	//	if (_frameX >= mouseCursor->GetMaxFrameX())
	//	{
	//		_frameX = 0;
	//	}
	//	mouseCursor->SetFrameX(_frameX);
	//	_frameX++;
	//}

}

void SubMap::Render(HDC hdc)
{
	switch (SUBWIN->GetFrameIndex())
	{
	case CTRL_NUM1:
		IMAGEMANAGER->FindImage("BaseMapCreep")->Render(hdc, 0, 200, CELL_WIDTH * 8, CELL_HEIGHT * 8);
		break;
	case CTRL_NUM2:
		for (int i = 0; i < TILE_SIZE_X; i++)
			{
				for (int j = 0; j < TILE_SIZE_Y; j++)
				{
					IMAGEMANAGER->FindImage("MapTile1")->FrameRender(hdc, CELL_WIDTH / 2 * i, CELL_HEIGHT / 2 * j + 200, i, j, CELL_WIDTH / 2, CELL_HEIGHT / 2);
				}
			}//end of for
			break;
	case CTRL_NUM3:
		for (int i = 0; i < TILE_SIZE_X; i++)
		{
			for (int j = 0; j < TILE_SIZE_Y; j++)
			{
				IMAGEMANAGER->FindImage("MapTile2")->FrameRender(hdc, CELL_WIDTH / 2 * i, CELL_HEIGHT / 2 * j + 200, i, j, CELL_WIDTH / 2, CELL_HEIGHT / 2);
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
	//mouseCursor->FrameRender(hdc, SUBWIN->GetPtMouse().x, SUBWIN->GetPtMouse().y, _frameX, _frameY);
}