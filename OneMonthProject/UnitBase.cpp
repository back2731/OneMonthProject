#include "stdafx.h"
#include "UnitBase.h"

UnitBase::UnitBase()
{
}

UnitBase::~UnitBase()
{
}

HRESULT UnitBase::Init()
{
	return E_NOTIMPL;
}

void UnitBase::Release()
{
}

void UnitBase::Update()
{
}

void UnitBase::Render(HDC hdc)
{
}

void UnitBase::RenderUI(HDC hdc)
{
}

int UnitBase::GetHatcheryX()
{
	return 0;
}

int UnitBase::GetHatcheryY()
{
	return 0;
}

int UnitBase::GetLarvaNumber()
{
	return 0;
}

void UnitBase::PlayAnimation()
{
	unitStatus.frameCount++;
	unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
	if (unitStatus.frameCount % 10 == 0)
	{
		unitStatus.frameCount = 0;
		if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
		{
			unitStatus.frameIndexX = 0;
		}
		unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
		unitStatus.frameIndexX++;
	}
}

void UnitBase::SetCommandSlot(int rectNumber, CommandBase* commandClass)
{
	commandSlot[rectNumber] = commandClass;
}

void UnitBase::SetCommandRect()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			commandRect[i * 3 + j] = RectMake(CAMERAMANAGER->GetCameraCenter().x + 335 + (j * 85), CAMERAMANAGER->GetCameraCenter().y + 225 + (i * 75), 70, 70);
		}
	}
}

void UnitBase::InitAstar()
{
	//cameraRect = { 0,0, WINSIZEX, WINSIZEY };

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			ZeroMemory(&tiles[j + i * TILEX], sizeof(TAGTILE));
			tiles[j + i * TILEX].rc = RectMake(CELL_HEIGHT * j, CELL_WIDTH * i, CELL_WIDTH, CELL_HEIGHT);
			tiles[j + i * TILEX].block = false;

			testRect[j + i * TILEX] = RectMakeCenter(tiles[j + i * TILEX].rc.left + (tiles[j + i * TILEX].rc.right - tiles[j + i * TILEX].rc.left) / 2,
				tiles[j + i * TILEX].rc.top + (tiles[j + i * TILEX].rc.bottom - tiles[j + i * TILEX].rc.top) / 2, 20, 20);
		}
	}

	LoadMap(0);


	currentSelect = SELECT_END;

	isFind = false;
	noPath = false;
	startAstar = false;
	isArrive = false;
}

void UnitBase::UpdateAstar(float unitX, float unitY)
{
	playerRect = RectMakeCenter(unitX, unitY, 15, 15);

	if (!startAstar)
	{
		for (int i = 0; i < TILESIZE; i++)
		{
			if (IntersectRect(&tempRect, &tiles[i].rc, &playerRect))
			{
				//if (IntersectRect(&tempRect, &testRect[i], &playerRect))
				//{
				startTile = i;
				//}
			}
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&tiles[i].rc, m_ptMouse))
			{
				switch (currentSelect)
				{
				case SELECT_END:
					endTile = i;
					endX = endTile % TILEX;
					endY = endTile / TILEX;
					break;
				case SELECT_BLOCK:
					tiles[i].block = true;
					break;
				}
			}
		}
	}//end of VK_LBUTTON

	switch (currentSelect)
	{
	case SELECT_END:
		if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		{
			isFind = false;
			noPath = false;
			startAstar = false;

			//for (int i = 0; i < openList.size(); i++)
			//{
			//	tiles[openList[i]].showState = STATE_NONE;
			//}
			//for (int i = 0; i < closeList.size(); i++)
			//{
			//	tiles[closeList[i]].showState = STATE_NONE;
			//}

			closeList.clear();
			openList.clear();
			saveRoad.clear();
			saveRoad.push_back(endTile);
			count = 0;
		}
		if (KEYMANAGER->IsOnceKeyUp(VK_RBUTTON))
		{
			startAstar = true;
			currentTile = startTile;
			//시작지점을 오픈리스트에 넣자
			openList.push_back(currentTile);
		}
		break;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&tiles[i].rc, m_ptMouse))
			{
				if (currentSelect == SELECT_BLOCK)
				{
					tiles[i + CAMERAMANAGER->GetCameraCenterX() / CELL_WIDTH + CAMERAMANAGER->GetCameraCenterY() / CELL_HEIGHT * TILEX].block = false;
				}
			}
		}
	}

	if (startTile != endTile)
	{
		if (!isFind && !noPath && startAstar)
		{
			while (!isFind && !noPath)
			{
				PlayAstar();
			}
		}
	}

	if (!saveRoad.empty())
	{
		startAstar = false;

		if (startTile + 1 == saveRoad.back())
		{
			unitStatus.unitRectX += SPEED;
		}
		if (startTile - 1 == saveRoad.back())
		{
			unitStatus.unitRectX -= SPEED;
		}
		if (startTile + 64 == saveRoad.back())
		{
			unitStatus.unitRectY += SPEED;
		}
		if (startTile - 64 == saveRoad.back())
		{
			unitStatus.unitRectY -= SPEED;
		}

		if (startTile + 65 == saveRoad.back())
		{
			unitStatus.unitRectX += SPEED2;
			unitStatus.unitRectY += SPEED2;
		}
		if (startTile - 65 == saveRoad.back())
		{
			unitStatus.unitRectX -= SPEED2;
			unitStatus.unitRectY -= SPEED2;
		}
		if (startTile - 63 == saveRoad.back())
		{
			unitStatus.unitRectX += SPEED2;
			unitStatus.unitRectY -= SPEED2;
		}
		if (startTile + 63 == saveRoad.back())
		{
			unitStatus.unitRectX -= SPEED2;
			unitStatus.unitRectY += SPEED2;
		}

		if (startTile == saveRoad.back())
		{
			saveRoad.pop_back();
		}
	}

	playerRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, 15, 15);

	CAMERAMANAGER->MoveCamera();
}

void UnitBase::RenderAstar(HDC hdc)
{
	if (KEYMANAGER->IsToggleKey(VK_F4))
	{
		for (int i = 0; i < TILESIZE; i++)
		{
			if (IntersectRect(&tempRect, &cameraRect, &tiles[i].rc))
			{
				if (tiles[i].block)
				{
					if (i == startTile)
					{
						startTile = -1;
					}
					if (i == endTile)
					{
						endTile = -1;
					}
					BeginSolidColor(hdc, &brush, RGB(0, 0, 255));
				}
				else if (i == startTile)
				{
					BeginSolidColor(hdc, &brush, RGB(0, 255, 0));
				}
				else if (i == endTile)
				{
					BeginSolidColor(hdc, &brush, RGB(255, 0, 0));
				}
				else if (tiles[i].showState == STATE_OPEN)
				{
					BeginSolidColor(hdc, &brush, RGB(128, 255, 255));
				}
				else if (tiles[i].showState == STATE_CLOSE)
				{
					BeginSolidColor(hdc, &brush, RGB(128, 255, 0));
				}
				else if (tiles[i].showState == STATE_PATH)
				{
					BeginSolidColor(hdc, &brush, RGB(255, 128, 128));
				}
				else
				{
					BeginSolidColor(hdc, &brush, RGB(255, 255, 255));
				}
				RectangleMake(hdc, tiles[i].rc);
				RectangleMake(hdc, testRect[i]);

				DeleteObject(brush);
			}
		}//end of for
	}

	BeginSolidColor(hdc, &brush, RGB(100, 100, 100));
	Rectangle(hdc, playerRect.left, playerRect.top, playerRect.right, playerRect.bottom);
	DeleteObject(brush);

	//sprintf_s(str, "count :  %d", count);
	//TextOut(hdc, 0, 0, str, strlen(str));

}

void UnitBase::PlayAstar()
{	//int currentTile = startTile;

	int currentX = currentTile % TILEX;
	int currentY = currentTile / TILEX;
	// left, right, up, down, leftup, rightdown, leftdown, rightup
	int dx[] = { -1, 1, 0, 0, -1, 1, -1, 1 };
	int dy[] = { 0, 0, -1, 1, -1, 1, 1, -1 };
	bool tempBlock[8];

	// 방향 찾는 반복문
	for (int i = 0; i < 8; i++)
	{
		int x = currentX + dx[i];
		int y = currentY + dy[i];
		tempBlock[i] = false;

		// 해당 방향으로 움직인 타일이 유효한 타일인지 확인
		if (0 <= x && x < TILEX && 0 <= y && y < TILEY)
		{
			bool isOpen;
			// 대각선 타일의 이동 문제로 (주변에 블락있으면 못감) 임시로 블락 상태 저장
			if (tiles[y * TILEX + x].block) tempBlock[i] = true;
			else {
				// check closeList z
				bool isClose = false;
				for (int j = 0; j < closeList.size(); j++)
				{
					if (closeList[j] == y * TILEX + x)
					{
						isClose = true;
						break;
					}
				}
				if (isClose) continue;

				if (i < 4)
				{
					tiles[y * TILEX + x].g = 10;
				}
				else
				{
					// leftup인 경우 left나 up에 블락있으면 안됨
					if (i == DIRECTION_LEFTUP &&
						tempBlock[DIRECTION_LEFT] || tempBlock[DIRECTION_UP]) continue;
					// rightdown인 경우 right나 down에 블락있으면 안됨
					if (i == DIRECTION_RIGHTDOWN &&
						tempBlock[DIRECTION_RIGHT] || tempBlock[DIRECTION_DOWN]) continue;
					// rightup인 경우 right나 up에 블락있으면 안됨
					if (i == DIRECTION_RIGHTUP &&
						tempBlock[DIRECTION_RIGHT] || tempBlock[DIRECTION_UP]) continue;
					// leftdown인 경우 left나 down에 블락있으면 안됨
					if (i == DIRECTION_LEFTDOWN &&
						tempBlock[DIRECTION_LEFT] || tempBlock[DIRECTION_DOWN]) continue;
					tiles[y * TILEX + x].g = 14;

				}
				//abs절대값

				tiles[y * TILEX + x].h = (abs(endX - x) + abs(endY - y)) * 10;
				tiles[y * TILEX + x].f = tiles[y * TILEX + x].g + tiles[y * TILEX + x].h;

				// 오픈리스트에 있으면 g 비용 비교 후 처리
				isOpen = false;
				for (int i = 0; i < openList.size(); i++)
				{
					if (openList[i] == y * TILEX + x)
					{
						isOpen = true;
						if (tiles[openList[i]].g > tiles[y * TILEX + x].g)
						{
							tiles[openList[i]].h = tiles[y * TILEX + x].h;
							tiles[openList[i]].g = tiles[y * TILEX + x].g;
							tiles[openList[i]].f = tiles[y * TILEX + x].f;
							tiles[openList[i]].node = currentTile;
						}
					}
				}
				// 없으면 그냥 넣고 부모 설정
				if (!isOpen)
				{
					openList.push_back(y * TILEX + x);
					tiles[y * TILEX + x].node = currentTile;
				}

				// find
				if (y * TILEX + x == endTile)
					isFind = true;

			}
		}
	}

	// 선택 지점 열린목록에서 빼기
	for (iter = openList.begin(); iter != openList.end(); ++iter)
	{
		if ((*iter) == currentTile)
		{
			iter = openList.erase(iter);
			break;
		}
	}

	// not Find
	if (openList.size() == 0)
	{

		noPath = true;

	}

	// 현재 타일 클로즈리스트에 넣기
	closeList.push_back(currentTile);

	if (openList.size() != 0)
	{
		// find minimum f cost in openList
		int min = tiles[*openList.begin()].h;
		currentTile = *openList.begin();
		for (iter = openList.begin(); iter != openList.end(); ++iter)
		{
			if (min > tiles[(*iter)].h)
			{
				min = tiles[(*iter)].h;
				currentTile = *iter;
			}
		}
	}

	// 타일 렌더를 위해 상태 저장
	for (int i = 0; i < openList.size(); i++)
	{
		tiles[openList[i]].showState = STATE_OPEN;
	}
	for (int i = 0; i < closeList.size(); i++)
	{
		tiles[closeList[i]].showState = STATE_CLOSE;
	}
	// 길 찾기 성공시 각 타일에 길찾기 상태 저장
	int tempTile = endTile;
	while (tiles[tempTile].node != startTile
		&& isFind)
	{
		tempTile = tiles[tempTile].node;
		tiles[tempTile].showState = STATE_PATH;
		saveRoad.push_back(tempTile);
	}

}

void UnitBase::LoadMap(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TAGTILE) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);

}

