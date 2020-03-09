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
	// ���������� ����, �� �߰�
	SCENEMANAGER->AddScene("SubMap", sub);

	// ���������� �ʱ�ȭ
#ifdef SUBWINOPEN
	SUBWIN->Init();
#endif // SUBWINOPEN

	// ���������� ����
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
	// ���������� ������Ʈ
#ifdef SUBWINOPEN
	SUBWIN->Update();
#endif // SUBWINOPEN

	if (KEYMANAGER->IsStayKeyDown('W')) { currentY += 5; }
	if (KEYMANAGER->IsStayKeyDown('S')) { currentY -= 5; }
	if (KEYMANAGER->IsStayKeyDown('A')) { currentX += 5; }
	if (KEYMANAGER->IsStayKeyDown('D')) { currentX -= 5; }

	if (KEYMANAGER->IsOnceKeyDown('B'))
	{
		openDoor = !openDoor;
	}

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
			//��ŭ �������� Ŭ���ߴ°��� ��ġȭ(�������� ����)
			cellX = cellX / (float)CELL_WIDTH;
		}
		int cellY = abs(m_ptMouse.y - currentY) / CELL_HEIGHT;
		cellY = (m_ptMouse.y < currentY) ? cellY * -1 : cellY;
		int locationX = (int)cellX;
		int locationY = (int)cellY;
		/*
		//���� x��ǥ�� 0���� ũ�� �ִ�Ÿ�ϼ� ���� �۰�
		//Y��ǥ 0���� ũ��, �ִ�Ÿ�ϼ����� ������ ������ �������
		*/
		if (locationX >= 0 && locationX < TILE_COUNT_X && locationY >= 0 && locationY < TILE_COUNT_Y)
		{
			SetMap(locationX, locationY, true); // �Ÿ������ �� locationX, locationY ��ŭ 
			_locationX = locationX;
			_locationY = locationY;
		}
	}
}

void MapToolScene::Render()
{
	// ���������� ������
#ifdef SUBWINOPEN
	SUBWIN->Render();
#endif // SUBWINOPEN

	//��ǥ ���.
	sprintf_s(str, "X : %d, Y : %d",
		_locationX + 1, _locationY + 1);
	TextOut(GetMemDC(), WINSIZEX - 100, 0, str, strlen(str));

	DrawTileMap();

	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			for (int z = 0; z < TILE_MAX; z++)
			{
				if (KEYMANAGER->IsToggleKey(VK_TAB))
				{
					if (_tileMap[i][j].tileKind[z] == TILEKIND_OBJECT)
					{
						Rectangle(GetMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);

						HBRUSH brush = CreateSolidBrush(RGB(204, 0, 102));
						FillRect(GetMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}
				}
			}
		}
	}

}

void MapToolScene::SetSubWindow()
{
	SetMapTool();
}

// Render ���ִ� �κ�
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

			_tileMap[i][j].left = left;
			_tileMap[i][j].top = top;
			_tileMap[i][j].right = right;
			_tileMap[i][j].bottom = bottom;

			_tileMap[i][j].rect = { _tileMap[i][j].left , _tileMap[i][j].top , _tileMap[i][j].right , _tileMap[i][j].bottom };


			for (int z = 0; z <= _tileMap[i][j].index; z++)
			{
				if (_tileMap[i][j].tileKind[z] != TILEKIND_NONE)
				{
					switch (_tileMap[i][j].tileKind[z])
					{
					case TILEKIND_TERRAIN:
						IMAGEMANAGER->FrameRender("mapTile", GetMemDC(),
							_tileMap[i][j].left, _tileMap[i][j].top, _tileMap[i][j].tilePos[z].x, _tileMap[i][j].tilePos[z].y);
						break;
					}
				}
			}

			if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
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
					sprintf_s(str, "(%d,%d)", i, j);
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

//�� �ʱ�ȭ.
void MapToolScene::SetMapTool()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			_tileMap[i][j].index = -1;
			_tileMap[i][j].height = 0;
		}
	}
}

//������Ʈ ���ִ� �κ�.
void MapToolScene::SetMap(int locationX, int locationY, bool isAdd)
{
	int index = SUBWIN->GetFrameIndex();

	switch (SUBWIN->GetFrameIndex())
	{
	case TILEKIND_NONE:
	case TILEKIND_TERRAIN:
	case TILEKIND_OBJECT:
	case TILEKIND_INVISIBLE_BLOCK:
	case TILEKIND_OPEN_DOOR:
	case TILEKIND_CLOSE_DOOR:

	case TILEKIND_ITEMHEART:
	case TILEKIND_ITEMGOLD:
	case TILEKIND_ITEMBOMB:
	case TILEKIND_ITEMATTACKBOMB:
	case TILEKIND_ITEMKEY:
	case TILEKIND_ITEMPILL:
	case TILEKIND_ITEMCARD:
	case TILEKIND_BLACKITEMBOXOPEN:
	case TILEKIND_BLACKITEMBOXCLOSE:
	case TILEKIND_GOLDITEMBOXOPEN:
	case TILEKIND_GOLDITEMBOXCLOSE:
	case TILEKIND_REDITEMBOXOPEN:
	case TILEKIND_REDITEMBOXCLOSE:
	case TILEKIND_CRACKEDITEMBOXOPEN:
	case TILEKIND_CRACKEDITEMBOXCLOSE:
	case TILEKIND_LOCKED_DOOR:
	case TILEKIND_USEDKEY_DOOR:
	case TILEKIND_POOP100:
	case TILEKIND_POOP50:
	case TILEKIND_POOP10:
	case TILEKIND_FIREPLACE:
	case TILEKIND_SHOP_HOST:
		imageFrame = SUBWIN->GetFramePoint();
		break;
	}
	_currentCTRL = SUBWIN->GetCTRL();

	switch (_currentCTRL)
	{
	case CTRL_DRAW:
		if (isAdd)
		{
			//if (SelectKind(imageFrame.x, imageFrame.y) == TILEKIND_OBJECT
			//	&& _tileMap[locationX][locationY].index == -1)
			//	break;

			_tileMap[locationX][locationY].index++;

			if (_tileMap[locationX][locationY].index >= TILE_MAX)
			{
				_tileMap[locationX][locationY].index = 0;
			}
			_tileMap[locationX][locationY].tileNum[_tileMap[locationX][locationY].index] = index;
			_tileMap[locationX][locationY].tileKind[_tileMap[locationX][locationY].index] = SelectKind(imageFrame.x, imageFrame.y);
			_tileMap[locationX][locationY].tilePos[_tileMap[locationX][locationY].index] = imageFrame;
		}
		else
		{
			//if (SelectKind(imageFrame.x, imageFrame.y) == TILEKIND_OBJECT)break;

			if (_tileMap[locationX][locationY].index == -1)
			{
				_tileMap[locationX][locationY].index++;

				if (_tileMap[locationX][locationY].index >= TILE_MAX)
				{
					_tileMap[locationX][locationY].index = TILE_MAX - 1;
				}
				_tileMap[locationX][locationY].tileNum[_tileMap[locationX][locationY].index] = index;
				_tileMap[locationX][locationY].tileKind[_tileMap[locationX][locationY].index] = SelectKind(imageFrame.x, imageFrame.y);
				_tileMap[locationX][locationY].tilePos[_tileMap[locationX][locationY].index] = imageFrame;
			}
		}
		break;
	case CTRL_ERASER:
		if (_tileMap[locationX][locationY].index > -1)
		{
			/*		_tileMap[locationX][locationY].tileNum[_tileMap[locationX][locationY].index] = index;
					_tileMap[locationX][locationY].tileKind[_tileMap[locationX][locationY].index] = SelectKind(-20, -20);
					_tileMap[locationX][locationY].tilePos[_tileMap[locationX][locationY].index] = imageFrame;*/

			for (int i = 0; i < TILE_MAX; i++)
			{
				_tileMap[locationX][locationY].tileNum[i] = 0;
				_tileMap[locationX][locationY].tileKind[i] = TILEKIND_NONE;
				_tileMap[locationX][locationY].tilePos[i] = { 0 };
			}
			index = -1;
		}
		break;
	}
}

// �Ӽ����� ������
TILEKIND MapToolScene::SelectKind(int frameX, int frameY)
{
	if (frameX == -20, frameY == -20)
	{
		return TILEKIND_NONE;
	}
	// �ʱⰪ�� �̰Ͷ����� ���� ����� �� ���߿� Ȯ���ϰ� �����غ���
	if (SUBWIN->GetFrameIndex() == CTRL_NUM1)
	{
		return TILEKIND_TERRAIN;
	}
	if (SUBWIN->GetFrameIndex() == CTRL_NUM2)
	{
		if (frameY == 0)
		{
			return TILEKIND_OBJECT;
		}
		if (frameY == 1)
		{
			return TILEKIND_ITEMHEART;
		}
		if (frameX <= 3 && frameY == 2)
		{
			return TILEKIND_ITEMGOLD;
		}
		if (frameX >= 4 && frameX <= 5 && frameY == 2)
		{
			return TILEKIND_ITEMBOMB;
		}
		if (frameX >= 6 && frameY == 2)
		{
			return TILEKIND_ITEMATTACKBOMB;
		}
		if (frameX <= 1 && frameY == 3)
		{
			return TILEKIND_ITEMKEY;
		}
		if (frameX >= 2 && frameX <= 4 && frameY == 3)
		{
			return TILEKIND_ITEMPILL;
		}
		if (frameX >= 5 && frameX <= 6 && frameY == 3)
		{
			return TILEKIND_ITEMCARD;
		}
		if (frameX == 7 && frameY == 3)
		{
			return TILEKIND_ITEMPOINT;
		}
		if (frameX == 0 && frameY == 4)
		{
			return TILEKIND_BLACKITEMBOXOPEN;
		}
		if (frameX == 1 && frameY == 4)
		{
			return TILEKIND_BLACKITEMBOXCLOSE;
		}
		if (frameX == 2 && frameY == 4)
		{
			return TILEKIND_GOLDITEMBOXOPEN;
		}
		if (frameX == 3 && frameY == 4)
		{
			return TILEKIND_GOLDITEMBOXCLOSE;
		}
		if (frameX == 4 && frameY == 4)
		{
			return TILEKIND_REDITEMBOXOPEN;
		}
		if (frameX == 5 && frameY == 4)
		{
			return TILEKIND_REDITEMBOXCLOSE;
		}
		if (frameX == 6 && frameY == 4)
		{
			return TILEKIND_CRACKEDITEMBOXOPEN;
		}
		if (frameX == 7 && frameY == 4)
		{
			return TILEKIND_CRACKEDITEMBOXCLOSE;
		}
		if (frameY == 5)
		{
			return TILEKIND_INVISIBLE_BLOCK;
		}
		if (frameY == 6 && frameX == 0)
		{
			return TILEKIND_POOP100;
		}
		if (frameY == 6 && frameX == 1)
		{
			return TILEKIND_POOP50;
		}
		if (frameY == 6 && frameX == 2)
		{
			return TILEKIND_POOP10;
		}
		if (frameY == 6 && frameX >= 3 && frameX <= 5)
		{
			return TILEKIND_FIREPLACE;
		}
		if (frameY == 6 && frameX >= 6)
		{
			return TILEKIND_SHOP_HOST;
		}
	}
	if (SUBWIN->GetFrameIndex() == CTRL_NUM3)
	{
		if (frameY >= 0 && frameY <= 5 && (frameX == 0 || frameX == 1 || frameX == 4 || frameX == 5))
		{
			return TILEKIND_OPEN_DOOR;
		}

		if (frameY >= 0 && frameY <= 5 && (frameX == 2 || frameX == 3 || frameX == 6 || frameX == 7))
		{
			return TILEKIND_CLOSE_DOOR;
		}

		if (frameY >= 6 && frameY <= 9 && (frameX == 0 || frameX == 1 || frameX == 4 || frameX == 5))
		{
			return TILEKIND_USEDKEY_DOOR;
		}

		if (frameY >= 6 && frameY <= 9 && (frameX == 2 || frameX == 3 || frameX == 6 || frameX == 7))
		{
			return TILEKIND_LOCKED_DOOR;
		}
	}
	return TILEKIND_NONE;

}

//�ʱ� �ε��� ���� // ������ ����.
void MapToolScene::TlieInit() // ��� �ε����� -1�� ó��
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			_tileMap[i][j].index = -1;
		}
	}
}
//�ε�
void MapToolScene::Load(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);
	CloseHandle(file);
}
//���̺�
void MapToolScene::Save(int saveCount)
{
	file = CreateFile(fileName[saveCount], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tileMap, sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y, &write, NULL);
	CloseHandle(file);
}