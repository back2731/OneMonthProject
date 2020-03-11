#include "stdafx.h"
#include "AStarScene.h"


aStarScene::aStarScene()
{
	//startTile = endTile = -1;
}


aStarScene::~aStarScene()
{
}

HRESULT aStarScene::Init()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			ZeroMemory(&tiles[j + i * TILEX], sizeof(tagTile));
			tiles[j + i * TILEX].rc = RectMake(CELL_HEIGHT * j, CELL_WIDTH * i, CELL_WIDTH, CELL_HEIGHT);
			tiles[j + i * TILEX].block = false;
		}
	}

	Load(0);



	currentSelect = SELECT_START;

	isFind = false;
	noPath = false;
	startAstar = false;
	isArrive = false;

	return S_OK;
}

void aStarScene::Release()
{
}

void aStarScene::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('1'))
	{
		currentSelect = SELECT_START;
	}
	if (KEYMANAGER->IsOnceKeyDown('2'))
	{
		currentSelect = SELECT_END;
	}
	if (KEYMANAGER->IsOnceKeyDown('3'))
	{
		currentSelect = SELECT_BLOCK;
	}
	if (KEYMANAGER->IsOnceKeyDown('4'))
	{
		if (startTile != -1 && endTile != -1)
		{
			startAstar = true;
			currentTile = startTile;
			//���������� ���¸���Ʈ�� ����
			openList.push_back(currentTile);
		}
	}

	if (KEYMANAGER->IsOnceKeyDown('5'))
	{
		openList.clear();
		closeList.clear();
		Init();
	}

	if (KEYMANAGER->IsStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&tiles[i].rc, m_ptMouse))
			{
				switch (currentSelect)
				{
				case SELECT_START:
					startTile = i + CAMERAMANAGER->GetCameraCenterX() / CELL_WIDTH + CAMERAMANAGER->GetCameraCenterY() / CELL_HEIGHT * TILEX;
					playerStart = i + CAMERAMANAGER->GetCameraCenterX() / CELL_WIDTH + CAMERAMANAGER->GetCameraCenterY() / CELL_HEIGHT * TILEX;
					playerRect = RectMakeCenter(tiles[playerStart].rc.left + (tiles[playerStart].rc.right - tiles[playerStart].rc.left) / 2,
						tiles[playerStart].rc.top + (tiles[playerStart].rc.bottom - tiles[playerStart].rc.top) / 2, 30, 30);
					break;
				case SELECT_END:
					endTile = i + CAMERAMANAGER->GetCameraCenterX() / CELL_WIDTH + CAMERAMANAGER->GetCameraCenterY() / CELL_HEIGHT * TILEX;
					endX = endTile % TILEX;
					endY = endTile / TILEX;
					break;
				case SELECT_BLOCK:
					tiles[i + CAMERAMANAGER->GetCameraCenterX() / CELL_WIDTH + CAMERAMANAGER->GetCameraCenterY() / CELL_HEIGHT * TILEX].block = true;
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

			for (int i = 0; i < openList.size(); i++)
			{
				tiles[openList[i]].showState = STATE_NONE;
			}
			for (int i = 0; i < closeList.size(); i++)
			{
				tiles[closeList[i]].showState = STATE_NONE;
			}

			openList.clear();
			closeList.clear();
			count = 0;
		}
		if (KEYMANAGER->IsOnceKeyUp(VK_RBUTTON))
		{
			startAstar = true;
			currentTile = startTile;
			//���������� ���¸���Ʈ�� ����
			openList.push_back(currentTile);
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_RBUTTON))
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

	if (!isFind && !noPath &&startAstar)
	{
		while (!isFind)
		{
			Astar();
		}
	}
	cameraRect = RectMake(CAMERAMANAGER->GetCameraXY().x - WINSIZEX, CAMERAMANAGER->GetCameraXY().y - WINSIZEY, WINSIZEX * 2, WINSIZEY * 2);

	CAMERAMANAGER->MoveCamera();
}

void aStarScene::Render()
{
	if (KEYMANAGER->IsToggleKey(VK_TAB))
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
					BeginSolidColor(GetMemDC(), &brush, RGB(0, 0, 255));
				}
				else if (i == startTile)
				{
					BeginSolidColor(GetMemDC(), &brush, RGB(0, 255, 0));
				}
				else if (i == endTile)
				{
					BeginSolidColor(GetMemDC(), &brush, RGB(255, 0, 0));
				}
				else if (tiles[i].showState == STATE_OPEN)
				{
					BeginSolidColor(GetMemDC(), &brush, RGB(128, 255, 255));
				}
				else if (tiles[i].showState == STATE_CLOSE)
				{
					BeginSolidColor(GetMemDC(), &brush, RGB(128, 255, 0));
				}
				else if (tiles[i].showState == STATE_PATH)
				{
					BeginSolidColor(GetMemDC(), &brush, RGB(255, 128, 128));
				}
				else
				{
					BeginSolidColor(GetMemDC(), &brush, RGB(255, 255, 255));
				}
				RectangleMake(GetMemDC(), tiles[i].rc);

				DeleteObject(brush);
			}
		}//end of for
	}

	BeginSolidColor(GetMemDC(), &brush, RGB(100, 100, 100));
	Rectangle(GetMemDC(), playerRect.left, playerRect.top, playerRect.right, playerRect.bottom);
	DeleteObject(brush);

	//sprintf_s(str, "count :  %d", count);
	//TextOut(GetMemDC(), 0, 0, str, strlen(str));
}

void aStarScene::Astar()
{
	//int currentTile = startTile;

	int currentX = currentTile % TILEX;
	int currentY = currentTile / TILEX;
	// left, right, up, down, leftup, rightdown, leftdown, rightup
	int dx[] = { -1, 1, 0, 0, -1, 1, -1, 1 };
	int dy[] = { 0, 0, -1, 1, -1, 1, 1, -1 };
	bool tempBlock[8];

	// ���� ã�� �ݺ���
	for (int i = 0; i < 8; i++)
	{
		int x = currentX + dx[i];
		int y = currentY + dy[i];
		tempBlock[i] = false;

		// �ش� �������� ������ Ÿ���� ��ȿ�� Ÿ������ Ȯ��
		if (0 <= x && x < TILEX && 0 <= y && y < TILEY)
		{
			bool isOpen;
			// �밢�� Ÿ���� �̵� ������ (�ֺ��� ��������� ����) �ӽ÷� ��� ���� ����
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
					// leftup�� ��� left�� up�� ��������� �ȵ�
					if (i == DIRECTION_LEFTUP &&
						tempBlock[DIRECTION_LEFT] || tempBlock[DIRECTION_UP]) continue;
					// rightdown�� ��� right�� down�� ��������� �ȵ�
					if (i == DIRECTION_RIGHTDOWN &&
						tempBlock[DIRECTION_RIGHT] || tempBlock[DIRECTION_DOWN]) continue;
					// rightup�� ��� right�� up�� ��������� �ȵ�
					if (i == DIRECTION_RIGHTUP &&
						tempBlock[DIRECTION_RIGHT] || tempBlock[DIRECTION_UP]) continue;
					// leftdown�� ��� left�� down�� ��������� �ȵ�
					if (i == DIRECTION_LEFTDOWN &&
						tempBlock[DIRECTION_LEFT] || tempBlock[DIRECTION_DOWN]) continue;
					tiles[y * TILEX + x].g = 14;

				}
				//abs���밪

				tiles[y * TILEX + x].h = (abs(endX - x) + abs(endY - y)) * 10;
				tiles[y * TILEX + x].f = tiles[y * TILEX + x].g + tiles[y * TILEX + x].h;

				// ���¸���Ʈ�� ������ g ��� �� �� ó��
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
				// ������ �׳� �ְ� �θ� ����
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

	// ���� ���� ������Ͽ��� ����
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

	// ���� Ÿ�� Ŭ�����Ʈ�� �ֱ�
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


	// Ÿ�� ������ ���� ���� ����
	for (int i = 0; i < openList.size(); i++)
	{
		tiles[openList[i]].showState = STATE_OPEN;
	}
	for (int i = 0; i < closeList.size(); i++)
	{
		tiles[closeList[i]].showState = STATE_CLOSE;
	}
	// �� ã�� ������ �� Ÿ�Ͽ� ��ã�� ���� ����
	int tempTile = endTile;
	while (tiles[tempTile].node != startTile
		&& isFind)
	{
		tempTile = tiles[tempTile].node;
		tiles[tempTile].showState = STATE_PATH;
	}
}

void aStarScene::Load(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}
