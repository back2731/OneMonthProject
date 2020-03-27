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

void UnitBase::RenderAirUint(HDC hdc)
{
}

void UnitBase::RenderShadow(HDC hdc)
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
	LoadMap(0);

	isFind = false;
	noPath = false;
	startAstar = false;
	isArrive = false;
}

void UnitBase::UpdateAstar(float unitX, float unitY)
{
	playerRect = RectMakeCenter(unitX, unitY, 5, 5);

	if (!startAstar)
	{
		for (int i = 0; i < TILESIZE; i++)
		{
			if (IntersectRect(&tempRect, &_tileMap[i].rect, &playerRect))
			{
				startTile = i;
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

}

void UnitBase::SetBlock()
{
	for (int i = 0; i < PLAYERMANAGER->GetBlockTileVector().size(); i++)
	{
		blockTile.push_back(PLAYERMANAGER->ReturnBlockTile(i));
	}
	for(int i = 0; i < blockTile.size(); i++)
	{
		_tileMap[blockTile[i]].block = true;
	}
	for (int i = 0; i < PLAYERMANAGER->GetGasTileVector().size(); i++)
	{
		gasTile.push_back(PLAYERMANAGER->ReturnGasTile(i));
	}
	for (int i = 0; i < gasTile.size(); i++)
	{
		//_tileMap[gasTile[i]].block = true;
		_tileMap[gasTile[i]].gas = true;
	}
}

void UnitBase::SetEndTile()
{
	for (int i = 0; i < TILESIZE; i++)
	{
		if (PtInRect(&_tileMap[i].rect, m_ptMouse) == _tileMap[i].block) continue;
		if (PtInRect(&_tileMap[i].rect, m_ptMouse))
		{
			{
				endTile = i;
				endX = endTile % TILEX;
				endY = endTile / TILEX;
			}
		}
	}
}

void UnitBase::SetEndTile(int num)
{
	for (int i = 0; i < TILESIZE; i++)
	{
		if (PtInRect(&_tileMap[i].rect, m_ptMouse) == _tileMap[i].block) continue;
		if (PtInRect(&_tileMap[i].rect, m_ptMouse))
		{
			{
				endTile = i + num;
				endX = endTile % TILEX;
				endY = endTile / TILEX;
			}
		}
	}
}

void UnitBase::SetAstarVector()
{
	isFind = false;
	noPath = false;
	startAstar = false;

	for (int i = 0; i < openList.size(); i++)
	{
		_tileMap[openList[i]].showState = STATE_NONE;
	}
	for (int i = 0; i < closeList.size(); i++)
	{
		_tileMap[closeList[i]].showState = STATE_NONE;
	}

	closeList.clear();
	openList.clear();
	saveRoad.clear();
	saveRoad.push_back(endTile);
	count = 0;

}

void UnitBase::SetStartTile()
{
	startAstar = true;
	currentTile = startTile;
	//���������� ���¸���Ʈ�� ����
	openList.push_back(currentTile);
}

void UnitBase::SetStartTile(int num)
{
	startAstar = true;
	currentTile = num;
	//���������� ���¸���Ʈ�� ����
	openList.push_back(currentTile);
}

void UnitBase::MoveUnit()
{
	if (!saveRoad.empty())
	{
		startAstar = false;

		if (startTile + 1 == saveRoad.back())
		{
			unitStatus.unitRectY += SPEED;
			//saveNumber = DIRECTION_DOWN;
			//return DIRECTION_DOWN;
		}
		if (startTile - 1 == saveRoad.back())
		{
			unitStatus.unitRectY -= SPEED;
			//saveNumber = DIRECTION_UP;
			//return DIRECTION_UP;
		}
		if (startTile + 64 == saveRoad.back())
		{
			unitStatus.unitRectX += SPEED;
			//saveNumber = DIRECTION_LEFT;
			//return DIRECTION_LEFT;
		}
		if (startTile - 64 == saveRoad.back())
		{
			unitStatus.unitRectX -= SPEED;
			//saveNumber = DIRECTION_RIGHT;
			//return DIRECTION_RIGHT;
		}

		if (startTile + 65 == saveRoad.back())
		{
			unitStatus.unitRectY += SPEED2;
			unitStatus.unitRectX += SPEED2;
		//	saveNumber = DIRECTION_RIGHTDOWN;
		//	return DIRECTION_RIGHTDOWN;
		}
		if (startTile - 65 == saveRoad.back())
		{
			unitStatus.unitRectY -= SPEED2;
			unitStatus.unitRectX -= SPEED2;
			//saveNumber = DIRECTION_RIGHTUP;
			//return DIRECTION_RIGHTUP;
		}
		if (startTile - 63 == saveRoad.back())
		{
			unitStatus.unitRectY += SPEED2;
			unitStatus.unitRectX -= SPEED2;
			//saveNumber = DIRECTION_LEFTDOWN;
			//return DIRECTION_LEFTDOWN;
		}
		if (startTile + 63 == saveRoad.back())
		{
			unitStatus.unitRectY -= SPEED2;
			unitStatus.unitRectX += SPEED2;
			//saveNumber = DIRECTION_LEFTUP;
			//return DIRECTION_LEFTUP;
		}

		if (startTile == saveRoad.back())
		{
			saveRoad.pop_back();
		}
	}

	//return saveNumber;

	//playerRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, 15, 15);
	//return DIRECTION_RIGHTDOWN;
}

int UnitBase::ChangeImageFrame()
{
	if (!saveRoad.empty())
	{
		startAstar = false;

		if (startTile + 1 == saveRoad.back())
		{
			saveNumber = DIRECTION_DOWN;
			return DIRECTION_DOWN;
		}
		if (startTile - 1 == saveRoad.back())
		{
			saveNumber = DIRECTION_UP;
			return DIRECTION_UP;
		}
		if (startTile + 64 == saveRoad.back())
		{
			saveNumber = DIRECTION_LEFT;
			return DIRECTION_LEFT;
		}
		if (startTile - 64 == saveRoad.back())
		{
			saveNumber = DIRECTION_RIGHT;
			return DIRECTION_RIGHT;
		}

		if (startTile + 65 == saveRoad.back())
		{
			saveNumber = DIRECTION_RIGHTDOWN;
			return DIRECTION_RIGHTDOWN;
		}
		if (startTile - 65 == saveRoad.back())
		{
			saveNumber = DIRECTION_RIGHTUP;
			return DIRECTION_RIGHTUP;
		}
		if (startTile - 63 == saveRoad.back())
		{
			saveNumber = DIRECTION_LEFTDOWN;
			return DIRECTION_LEFTDOWN;
		}
		if (startTile + 63 == saveRoad.back())
		{
			saveNumber = DIRECTION_LEFTUP;
			return DIRECTION_LEFTUP;
		}
	}
	return saveNumber;
}

void UnitBase::PlayAstar()
{	//int currentTile = startTile;

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
			if (_tileMap[y * TILEX + x].block) tempBlock[i] = true;
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
					_tileMap[y * TILEX + x].g = 10;
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
					_tileMap[y * TILEX + x].g = 14;

				}
				//abs���밪

				_tileMap[y * TILEX + x].h = (abs(endX - x) + abs(endY - y)) * 10;
				_tileMap[y * TILEX + x].f = _tileMap[y * TILEX + x].g + _tileMap[y * TILEX + x].h;

				// ���¸���Ʈ�� ������ g ��� �� �� ó��
				isOpen = false;
				for (int i = 0; i < openList.size(); i++)
				{
					if (openList[i] == y * TILEX + x)
					{
						isOpen = true;
						if (_tileMap[openList[i]].g > _tileMap[y * TILEX + x].g)
						{
							_tileMap[openList[i]].h = _tileMap[y * TILEX + x].h;
							_tileMap[openList[i]].g = _tileMap[y * TILEX + x].g;
							_tileMap[openList[i]].f = _tileMap[y * TILEX + x].f;
							_tileMap[openList[i]].node = currentTile;
						}
					}
				}
				// ������ �׳� �ְ� �θ� ����
				if (!isOpen)
				{
					openList.push_back(y * TILEX + x);
					_tileMap[y * TILEX + x].node = currentTile;
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
		int min = _tileMap[*openList.begin()].h;
		currentTile = *openList.begin();
		for (iter = openList.begin(); iter != openList.end(); ++iter)
		{
			if (min > _tileMap[(*iter)].h)
			{
				min = _tileMap[(*iter)].h;
				currentTile = *iter;
			}
		}
	}

	// Ÿ�� ������ ���� ���� ����
	for (int i = 0; i < openList.size(); i++)
	{
		_tileMap[openList[i]].showState = STATE_OPEN;
	}
	for (int i = 0; i < closeList.size(); i++)
	{
		_tileMap[closeList[i]].showState = STATE_CLOSE;
	}
	// �� ã�� ������ �� Ÿ�Ͽ� ��ã�� ���� ����
	int tempTile = endTile;
	while (_tileMap[tempTile].node != startTile
		&& isFind)
	{
		tempTile = _tileMap[tempTile].node;
		_tileMap[tempTile].showState = STATE_PATH;
		saveRoad.push_back(tempTile);
	}

}

void UnitBase::LoadMap(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TAGTILE) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}

void UnitBase::SetEndTileATK(int num)
{
	endTile = num;
	endX = endTile % TILEX;
	endY = endTile / TILEX;
}

