#include "stdafx.h"
#include "MapToolScene.h"


MapToolScene::MapToolScene()
{
}


MapToolScene::~MapToolScene()
{
}

HRESULT MapToolScene::Init()
{
	// 서브윈도우 선언, 씬 추가
	SCENEMANAGER->AddScene("SubMap", sub);

	// 서브윈도우 초기화
#ifdef SUBWINOPEN
	SUBWIN->Init();
#endif // SUBWINOPEN

	// 서브윈도우 세팅
#ifdef SUBWINOPEN
	SUBWIN->SetScene(sub);
#endif // SUBWINOPEN

	_locationX = 0;
	_locationY = 0;
	_center = 0;
	memset(_tileMap, 0, sizeof(_tileMap));

	currentX = 0;
	currentY = 0;

	_isDebug = true;
	_currentCTRL = CTRL_DRAW;

	openDoor = false;

	SetMapTool();

	return S_OK;
}

void MapToolScene::Release()
{
}

void MapToolScene::Update()
{
	// 서브윈도우 업데이트
#ifdef SUBWINOPEN
	SUBWIN->Update();
#endif // SUBWINOPEN

	if (KEYMANAGER->IsStayKeyDown('W')) { currentY += 10; }
	if (KEYMANAGER->IsStayKeyDown('S')) { currentY -= 10; }
	if (KEYMANAGER->IsStayKeyDown('A')) { currentX += 10; }
	if (KEYMANAGER->IsStayKeyDown('D')) { currentX -= 10; }

	if (KEYMANAGER->IsOnceKeyDown(VK_TAB))
	{
		_isDebug = !_isDebug;
	}

	if (!SUBWIN->GetIsActive() && KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		float cellX = (float)(m_ptMouse.x - currentX);

		if (cellX < 0)
		{
			cellX = cellX / (float)CELL_WIDTH;
		}
		else
		{
			//얼만큼 떨어져서 클릭했는가를 수치화(가로지름 기준)
			cellX = cellX / (float)CELL_WIDTH;
		}
		int cellY = abs(m_ptMouse.y - currentY) / CELL_HEIGHT;
		cellY = (m_ptMouse.y < currentY) ? cellY * -1 : cellY;
		int locationX = (int)cellX;
		int locationY = (int)cellY;
		/*
		//만약 x좌표가 0보다 크고 최대타일수 보다 작고
		//Y좌표 0보다 크고, 최대타일수보다 작으면 검출대상에 집어넣자
		*/
		if (locationX >= 0 && locationX < TILE_COUNT_X && locationY >= 0 && locationY < TILE_COUNT_Y)
		{
			SetMap(locationX, locationY, true); // 거리계산이 된 locationX, locationY 만큼 
			_locationX = locationX;
			_locationY = locationY;
		}
	}
}

void MapToolScene::Render()
{
	// 서브윈도우 랜더링
#ifdef SUBWINOPEN
	SUBWIN->Render();
#endif // SUBWINOPEN

	//좌표 출력.
	sprintf_s(str, "%d", _locationX * TILE_COUNT_X + _locationY);
	TextOut(GetMemDC(), WINSIZEX - 100, 0, str, strlen(str));

	DrawTileMap();
}

void MapToolScene::SetSubWindow()
{
	SetMapTool();
}

// Render 해주는 부분
void MapToolScene::DrawTileMap()
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

			_tileMap[i*TILE_COUNT_X + j].rect = { _tileMap[i*TILE_COUNT_X + j].left , _tileMap[i*TILE_COUNT_X + j].top , _tileMap[i*TILE_COUNT_X + j].right , _tileMap[i*TILE_COUNT_X + j].bottom };

			if (IntersectRect(&temp, &cameraRect, &_tileMap[i*TILE_COUNT_X + j].rect))
			{
				if (_tileMap[i*TILE_COUNT_X + j].tileKind != TILEKIND_NONE)
				{
					switch (_tileMap[i*TILE_COUNT_X + j].tileKind)
					{

					case TILEKIND_TERRAIN:
						IMAGEMANAGER->FrameRender("BaseMap", GetMemDC(),
							_tileMap[i*TILE_COUNT_X + j].left, _tileMap[i*TILE_COUNT_X + j].top, _tileMap[i*TILE_COUNT_X + j].tilePos.x, _tileMap[i*TILE_COUNT_X + j].tilePos.y);
						break;
					case TILEKIND_TERRAIN2:
						IMAGEMANAGER->FrameRender("MapTile1", GetMemDC(),
							_tileMap[i*TILE_COUNT_X + j].left, _tileMap[i*TILE_COUNT_X + j].top, _tileMap[i*TILE_COUNT_X + j].tilePos.x, _tileMap[i*TILE_COUNT_X + j].tilePos.y);
						break;
					case TILEKIND_TERRAIN3:
						IMAGEMANAGER->FrameRender("MapTile2", GetMemDC(),
							_tileMap[i*TILE_COUNT_X + j].left, _tileMap[i*TILE_COUNT_X + j].top, _tileMap[i*TILE_COUNT_X + j].tilePos.x, _tileMap[i*TILE_COUNT_X + j].tilePos.y);
						break;
					}
				}
			}

			if (IntersectRect(&temp, &debugRect, &_tileMap[i*TILE_COUNT_X + j].rect))
			{
				if (_isDebug)
				{
					if (j % 11 == 0)
					{
						DrawLineX(left, top);
					}
					if (i % 17 == 0)
					{
						DrawLineY(left, top);
					}

					if (j % 1 == 0)
					{
						DrawLineX(left, top);
					}
					if (i % 1 == 0)
					{
						DrawLineY(left, top);
					}
					SetTextColor(GetMemDC(), RGB(255, 0, 0));
					sprintf_s(str, "(%d)", i*TILE_COUNT_X + j);
					TextOut(GetMemDC(),
						left + CELL_WIDTH / 2 - 20,
						top + CELL_HEIGHT / 2 - 10, str, strlen(str));
				}
			}
		}
	}
}

void MapToolScene::DrawLineX(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(GetMemDC(), centerX, centerY, centerX + CELL_WIDTH, centerY);
}
void MapToolScene::DrawLineY(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(GetMemDC(), centerX, centerY, centerX, centerY + CELL_HEIGHT);
}

//맵 초기화.
void MapToolScene::SetMapTool()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			_tileMap[i*TILE_COUNT_X + j].tileKind = TILEKIND_NONE;
			//_tileMap[i*TILE_COUNT_X+j].tilePos = PointMake(1, 0);
		}
	}
}

//업데이트 해주는 부분.
void MapToolScene::SetMap(int locationX, int locationY, bool isAdd)
{
	int index = SUBWIN->GetFrameIndex();

	switch (SUBWIN->GetFrameIndex())
	{
	case CTRL_NUM1:
	case CTRL_NUM2:
	case CTRL_NUM3:

		imageFrame = SUBWIN->GetFramePoint();
		break;
	}
	_currentCTRL = SUBWIN->GetCTRL();

	switch (_currentCTRL)
	{
	case CTRL_DRAW:
		if (isAdd)
		{
			/*_tileMap[locationX][locationY].index++;

			if (_tileMap[locationX][locationY].index >= TILE_MAX)
			{
				_tileMap[locationX][locationY].index = 0;
			}*/
			//_tileMap[locationX][locationY].tileNum[_tileMap[locationX][locationY].index] = index;
			_tileMap[locationX*TILE_COUNT_X+locationY].tileKind = SelectKind(imageFrame.x, imageFrame.y);
			_tileMap[locationX*TILE_COUNT_X+locationY].tilePos = imageFrame;
		}
		else
		{
			//if (_tileMap[locationX][locationY].index == -1)
			//{
			//	_tileMap[locationX][locationY].index++;

			//	if (_tileMap[locationX][locationY].index >= TILE_MAX)
			//	{
			//		_tileMap[locationX][locationY].index = TILE_MAX - 1;
			//	}
				//_tileMap[locationX][locationY].tileNum[_tileMap[locationX][locationY].index] = index;
			{	_tileMap[locationX*TILE_COUNT_X+locationY].tileKind = SelectKind(imageFrame.x, imageFrame.y);
				_tileMap[locationX*TILE_COUNT_X+locationY].tilePos = imageFrame;
			}
		}
		break;
	case CTRL_ERASER:
		//if (_tileMap[locationX][locationY].index > -1)
		//{
		//	for (int i = 0; i < TILE_MAX; i++)
		//	{
				//_tileMap[locationX][locationY].tileNum[i] = 0;
			{
				_tileMap[locationX*TILE_COUNT_X+locationY].tileKind = TILEKIND_NONE;
				_tileMap[locationX*TILE_COUNT_X+locationY].tilePos = { 0 };
			}
		//	index = -1;
		//}
		break;
	}
}

// 속성종류 정해줌
TILEKIND MapToolScene::SelectKind(int frameX, int frameY)
{
	if (frameX == -20, frameY == -20)
	{
		return TILEKIND_NONE;
	}
	// 초기값이 이것때문에 문제 생기는 것 나중에 확인하고 수정해보자
	if (SUBWIN->GetFrameIndex() == CTRL_NUM1)
	{
		return TILEKIND_TERRAIN;
	}
	if (SUBWIN->GetFrameIndex() == CTRL_NUM2)
	{
		return TILEKIND_TERRAIN2;
	}
	if (SUBWIN->GetFrameIndex() == CTRL_NUM3)
	{
		return TILEKIND_TERRAIN3;
	}
	return TILEKIND_NONE;

}

//초기 인덱스 지정 // 사용되지 않음.
void MapToolScene::TlieInit() // 모든 인덱스를 -1로 처리
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			//_tileMap[i][j].index = -1;
		}
	}
}
//로드
void MapToolScene::Load(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TAGTILE) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);
	CloseHandle(file);
}
//세이브
void MapToolScene::Save(int saveCount)
{
	file = CreateFile(fileName[saveCount], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tileMap, sizeof(TAGTILE) * TILE_COUNT_X * TILE_COUNT_Y, &write, NULL);
	CloseHandle(file);
}
