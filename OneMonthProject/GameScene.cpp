#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

HRESULT GameScene::Init()
{
	LoadMap(0);
	buildingVector.reserve(1000);
	unitVector.reserve(1000);
	airUnitVector.reserve(1000);
	selectVector.reserve(50);
	

	consoleImage = IMAGEMANAGER->FindImage("ZergConsole");

	// �ʱ� ��ó�� ����
	buildingVector.push_back(BUILDMANAGER->CreateHatchery(PLAYER1, { 64 * 7, 64 * 4 }));
	
	buildingVector.push_back(BUILDMANAGER->CreateHatchery(PLAYER2, { 64 * 2, 64 * 2 }));

	gas = RectMake(64 * 10, 64 * 8, 64 * 4, 64 * 2);
	for (int i = 0; i < TILESIZE; i++)
	{
		if (IntersectRect(&tempRect, &_tileMap[i].rect, &gas))
		{
			_tileMap[i].gas = true;
			PLAYERMANAGER->SetGasTile(i);
		}
	}

	// �ش� �ǹ��� ��ó����� ��ٸ� �������ش�
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetBuildKind() == HATCHERY)
		{
			if (buildingVector[i]->GetBuildingPlayerNumber() == PLAYER1)
			{
				unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER1, { buildingVector[i]->GetBuildingRectX() - 70, buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 1));
				unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER1, { buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 2));
				unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER1, { buildingVector[i]->GetBuildingRectX() + 70, buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 3));

				buildingVector[i]->SetCurrentLarva(LARVAMAX);
			}
			else if (buildingVector[i]->GetBuildingPlayerNumber() == PLAYER2)
			{
				unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER2, { buildingVector[i]->GetBuildingRectX() - 70, buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 1));
				unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER2, { buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 2));
				unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER2, { buildingVector[i]->GetBuildingRectX() + 70, buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 3));

				buildingVector[i]->SetCurrentLarva(LARVAMAX);
			}
		}
	}

	mineralImage = IMAGEMANAGER->FindImage("mineral");
	vespeneGasImage = IMAGEMANAGER->FindImage("gas");
	populationImage = IMAGEMANAGER->FindImage("population");
	
	maxPopulation = 9;
	return S_OK;
}

void GameScene::Release()
{
}

void GameScene::Update()
{
	BUILDMANAGER->SetHaveHatchery(false);
	BUILDMANAGER->SetHaveLair(false);
	BUILDMANAGER->SetHaveHive(false);
	BUILDMANAGER->SetHaveSpawningpool(false);
	BUILDMANAGER->SetHaveHydraliskden(false);
	BUILDMANAGER->SetHaveEvolutionchamber(false);
	BUILDMANAGER->SetHaveCreepcolony(false);
	BUILDMANAGER->SetHaveSpire(false);
	BUILDMANAGER->SetHaveQueensnest(false);
	BUILDMANAGER->SetHaveUltraliskcavern(false);

	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetBuildKind() == HATCHERY)
		{
			BUILDMANAGER->SetHaveHatchery(true);
		}
		if (buildingVector[i]->GetBuildKind() == LAIR)
		{
			BUILDMANAGER->SetHaveHatchery(true);
			BUILDMANAGER->SetHaveLair(true);
		}
		if (buildingVector[i]->GetBuildKind() == HIVE)
		{
			BUILDMANAGER->SetHaveHatchery(true);
			BUILDMANAGER->SetHaveLair(true);
			BUILDMANAGER->SetHaveHive(true);
		}
		if (buildingVector[i]->GetBuildKind() == SPAWNINGPOOL)
		{
			BUILDMANAGER->SetHaveSpawningpool(true);
		}
		if (buildingVector[i]->GetBuildKind() == HYDRALISKDEN)
		{
			BUILDMANAGER->SetHaveHydraliskden(true);
		}
		if (buildingVector[i]->GetBuildKind() == EVOLUTIONCHAMBER)
		{
			BUILDMANAGER->SetHaveEvolutionchamber(true);
		}
		if (buildingVector[i]->GetBuildKind() == CREEPCOLONY)
		{
			BUILDMANAGER->SetHaveCreepcolony(true);
		}
		if (buildingVector[i]->GetBuildKind() == SPIRE)
		{
			BUILDMANAGER->SetHaveSpire(true);
		}
		if (buildingVector[i]->GetBuildKind() == QUEENSNEST)
		{
			BUILDMANAGER->SetHaveQueensnest(true);
		}
		if (buildingVector[i]->GetBuildKind() == ULTRALISKCAVERN)
		{
			BUILDMANAGER->SetHaveUltraliskcavern(true);
		}
		if (buildingVector[i]->GetBuildKind() == DEFILERMOUND)
		{
			BUILDMANAGER->SetHaveDefilerMound(true);
		}
	}

	ShowCursor(false);
	
	commandRect = RectMake(CAMERAMANAGER->GetCameraCenter().x + 335, CAMERAMANAGER->GetCameraCenter().y + 225, 250, 250);
	cameraRect1 = RectMake(CAMERAMANAGER->GetCameraXY().x - WINSIZEX, CAMERAMANAGER->GetCameraXY().y - WINSIZEY, WINSIZEX * 2, WINSIZEY * 2);
	cameraRect2 = RectMake(CAMERAMANAGER->GetCameraXY().x, CAMERAMANAGER->GetCameraXY().y, WINSIZEX, WINSIZEY);

	// ��� �ǹ� ������Ʈ
	for (int i = 0; i < buildingVector.size(); i++)
	{
		buildingVector[i]->Update();
	}
	// ���� ���� ������Ʈ
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->Update();
	}
	// ���� ���� ������Ʈ
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		airUnitVector[i]->Update();
	}

	// �ش� �ǹ��� Ŭ�� ���� �� ���¸� �������ִ� �κ�
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (PtInRect(&buildingVector[i]->GetBuildingRect(), m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				dragRect.left = m_ptMouse.x;
				dragRect.top = m_ptMouse.y;

				for (int j = 0; j < buildingVector.size(); j++)
				{
					buildingVector[j]->SetIsClick(false);
					buildingVector[i]->SetIsClick(true);
					
					for (int k = 0; k < unitVector.size(); k++)
					{
						unitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < airUnitVector.size(); k++)
					{
						airUnitVector[k]->SetIsClick(false);
					}
				}
			}
		}
	}

	// �ش� ���� ������ Ŭ�� ���� �� ���¸� �������ִ� �κ�
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (PtInRect(&unitVector[i]->GetUnitRect(), m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				dragRect.left = m_ptMouse.x;
				dragRect.top = m_ptMouse.y;

				for (int j = 0; j < unitVector.size(); j++)
				{
					unitVector[j]->SetIsClick(false);
					unitVector[i]->SetIsClick(true);

					for (int k = 0; k < buildingVector.size(); k++)
					{
						buildingVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < airUnitVector.size(); k++)
					{
						airUnitVector[k]->SetIsClick(false);
					}
				}
			}
		}
	}

	// �ش� ���� ������ Ŭ�� ���� �� ���¸� �������ִ� �κ�
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (PtInRect(&airUnitVector[i]->GetUnitRect(), m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				dragRect.left = m_ptMouse.x;
				dragRect.top = m_ptMouse.y;

				for (int j = 0; j < airUnitVector.size(); j++)
				{
					airUnitVector[j]->SetIsClick(false);
					airUnitVector[i]->SetIsClick(true);

					for (int k = 0; k < buildingVector.size(); k++)
					{
						buildingVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < unitVector.size(); k++)
					{
						unitVector[k]->SetIsClick(false);
					}
				}
			}
		}
	}

	// ��ó��(����, ���̺�)���� ����Ʈ ��ٸ� ������ ��
	if (UNITMANAGER->GetSelectLarvaValue())
	{
		for (int i = 0; i < buildingVector.size(); i++)
		{
			buildingVector[i]->SetIsClick(false);
		}

		for (int i = 0; i < unitVector.size(); i++)
		{
			if (unitVector[i]->GetHatcheryX() == UNITMANAGER->GetSaveX() && unitVector[i]->GetHatcheryY() == UNITMANAGER->GetSaveY())
			{
				unitVector[i]->SetIsClick(true);
			}
		}
		UNITMANAGER->SetSelectLarva(false);
	}

	// ����� ���� ������ ���� ���Ͱ� 0���� Ŭ�� �Լ��� ���� �����´�.
	if (UNITMANAGER->GetTempVector().size() > 0)
	{
		while (UNITMANAGER->GetTempVector().size() > 0)
		{
			unitVector.push_back(UNITMANAGER->ReturnUnitVector());
		}
	}

	// ����� ���� ������ ���� ���Ͱ� 0���� Ŭ�� �Լ��� ���� �����´�.
	if (UNITMANAGER->GetAirUnitVector().size() > 0)
	{
		while (UNITMANAGER->GetAirUnitVector().size() > 0)
		{
			airUnitVector.push_back(UNITMANAGER->ReturnAirUnitVector());
		}
	}

	// ����� �ǹ��� ���� ���Ͱ� 0���� Ŭ�� �Լ��� ���� �����´�.
	if (BUILDMANAGER->GetTempVector().size() > 0)
	{
		while (BUILDMANAGER->GetTempVector().size() > 0)
		{
			buildingVector.push_back(BUILDMANAGER->ReturnBuildingVector());
		}
	}

	// ���¸� ��ġ�� ���� �� ��ó�� ���� ��� �� ����
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetUnitKind() == LARVA)
		{
			if (unitVector[i]->GetIsTransform())
			{
				unitVector[i]->SetIsClick(false);
				for (int j = 0; j < buildingVector.size(); j++)
				{
					if (unitVector[i]->GetHatcheryX() == buildingVector[j]->GetBuildingRectX() &&
						unitVector[i]->GetHatcheryY() == buildingVector[j]->GetBuildingRectY())
					{
						buildingVector[j]->SetCurrentLarva(-1);
					}
				}
				unitVector.erase(unitVector.begin() + i);
			}
		}
	}

	// ���¸� ��ġ�� ��� ���� ����
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetUnitKind() == DRONE)
		{
			if (unitVector[i]->GetIsTransform())
			{
				unitVector.erase(unitVector.begin() + i);
			}
		}
	}

	// ��� �ڵ� ���� ���
	count++;
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetBuildingPlayerNumber() == PLAYER1 && 
			(buildingVector[i]->GetBuildKind() == HATCHERY || 
				buildingVector[i]->GetBuildKind() == LAIR || 
				buildingVector[i]->GetBuildKind() == HIVE))
		{
			if (buildingVector[i]->GetCurrentLarva() < LARVAMAX)
			{
				if (count % 200 == 0)
				{
					unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER1, { buildingVector[i]->GetBuildingRectX() - 70 + (70 * RND->GetInt(2)), buildingVector[i]->GetBuildingRect().bottom + 25 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 1));
					buildingVector[i]->SetCurrentLarva(+1);
					count = 0;
				}
			}
		}
		if (buildingVector[i]->GetBuildingPlayerNumber() == PLAYER2)
		{
			if (buildingVector[i]->GetCurrentLarva() < LARVAMAX)
			{
				if (count % 200 == 0)
				{
					unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER2, { buildingVector[i]->GetBuildingRectX() - 70 + (70 * RND->GetInt(2)), buildingVector[i]->GetBuildingRect().bottom + 25 + RND->GetInt(3) }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 1));
					buildingVector[i]->SetCurrentLarva(+1);
					count = 0;
				}
			}
		}
	}

	// ���ְ��� �浹ó�� �Լ�
	COLLISIONMANAGER->CollisionSameVector(unitVector, KNOCKBACK * 0.2);
	COLLISIONMANAGER->CollisionSameVector(airUnitVector, KNOCKBACK * 2);
	COLLISIONMANAGER->CollisionUnitToBuilding(unitVector, buildingVector);

	// ����� ����Ǹ� false�� �����ϴ� �Լ�
	UNITMANAGER->SetInputCommandTransDrone(false);
	UNITMANAGER->SetInputCommandTransZergling(false);
	UNITMANAGER->SetInputCommandTransOverlord(false);
	UNITMANAGER->SetInputCommandTransHydralisk(false);
	UNITMANAGER->SetInputCommandTransMutalisk(false);
	UNITMANAGER->SetInputCommandTransScourge(false);
	UNITMANAGER->SetInputCommandTransQueen(false);
	UNITMANAGER->SetInputCommandTransUltralisk(false);
	UNITMANAGER->SetInputCommandTransDefiler(false);

	PLAYERMANAGER->SetInputCommandMove(false);

	// �巡�� ��ɹ�
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		dragRect.left = m_ptMouse.x;
		dragRect.top = m_ptMouse.y;
		dragRect.right = m_ptMouse.x;
		dragRect.bottom = m_ptMouse.y;

		if (!PtInRect(&commandRect, m_ptMouse))
		{
			for (int i = 0; i < buildingVector.size(); i++)
			{
				buildingVector[i]->SetIsClick(false);
			}
			for (int i = 0; i < unitVector.size(); i++)
			{
				unitVector[i]->SetIsClick(false);
			}
			for (int i = 0; i < airUnitVector.size(); i++)
			{
				airUnitVector[i]->SetIsClick(false);
			}
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		dragRect.right = m_ptMouse.x;
		dragRect.bottom = m_ptMouse.y;			
	}
	if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
	{
		dragRect.right = m_ptMouse.x;
		dragRect.bottom = m_ptMouse.y;
	}

	// �巡�׵� ���� ���� ���� ��ɹ�
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &dragRect, &unitVector[i]->GetUnitRect()))
		{
	 		unitVector[i]->SetIsClick(true);
			for (int i = 0; i < buildingVector.size(); i++)
			{
				buildingVector[i]->SetIsClick(false);
			}
		}
	}
	// �巡�׵� ���� ���� ���� ��ɹ�
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &dragRect, &airUnitVector[i]->GetUnitRect()))
		{
			airUnitVector[i]->SetIsClick(true);
			for (int i = 0; i < buildingVector.size(); i++)
			{
				buildingVector[i]->SetIsClick(false);
			}
		}
	}
	
	maxPopulation = PLAYERMANAGER->GetmaxPopulation();
	if (maxPopulation >= 200)
	{
		maxPopulation = 200;
	}
	currentPopulation = PLAYERMANAGER->GetCurrentPopulation();
	if (currentPopulation >= 200)
	{
		currentPopulation = 200;
	}
	if (currentPopulation < 0)
	{
		currentPopulation = 0;
	}
	// ���� �Ϸ��� ����
	for (int i = 0; i < unitVector.size(); i++)
	{
		for (int j = 0; j < unitVector.size(); j++)
		{
			if (unitVector[i]->GetUnitPlayerNumber() == PLAYER1 && unitVector[j]->GetUnitPlayerNumber() != PLAYER1)
			{
				if (IntersectRect(&tempRect, &unitVector[i]->GetunitSearchingRect(), &unitVector[j]->GetUnitRect()))
				{
					if (count % 20 == 0)
					{
						unitVector[j]->SetUnitHp(unitVector[j]->GetUnitHp() - unitVector[i]->GetUnitATK());
					}
					unitVector[i]->SetIsSearch(true);
				}
				else
				{
					unitVector[i]->SetIsSearch(false);
				}
			}
		}

		for (int k = 0; k < buildingVector.size(); k++)
		{
			if (unitVector[i]->GetUnitPlayerNumber() == PLAYER1 && buildingVector[k]->GetBuildingPlayerNumber() != PLAYER1)
			{
				if (IntersectRect(&tempRect, &unitVector[i]->GetunitSearchingRect(), &buildingVector[k]->GetBuildingRect()))
				{
					if (count % 10 == 0)
					{
						buildingVector[k]->SetBuildingHP(buildingVector[k]->GetBuildingHP() - unitVector[i]->GetUnitATK());
					}
					unitVector[i]->SetIsSearch(true);
				}
				else
				{
					unitVector[i]->SetIsSearch(false);
				}
			}
		}
	}
}

void GameScene::Render()
{
	DrawTileMap();

	// ��Ʈ �׽�Ʈ��
	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		for (int i = 0; i < buildingVector.size(); i++)
		{
			Rectangle(GetMemDC(), buildingVector[i]->GetBuildingRect().left, buildingVector[i]->GetBuildingRect().top, buildingVector[i]->GetBuildingRect().right, buildingVector[i]->GetBuildingRect().bottom);
		}

		for (int i = 0; i < unitVector.size(); i++)
		{
			Rectangle(GetMemDC(), unitVector[i]->GetUnitRect().left, unitVector[i]->GetUnitRect().top, unitVector[i]->GetUnitRect().right, unitVector[i]->GetUnitRect().bottom);
		}

		for (int i = 0; i < airUnitVector.size(); i++)
		{
			Rectangle(GetMemDC(), airUnitVector[i]->GetUnitRect().left, airUnitVector[i]->GetUnitRect().top, airUnitVector[i]->GetUnitRect().right, airUnitVector[i]->GetUnitRect().bottom);
		}
	}

	// ���� ���� ������
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &unitVector[i]->GetUnitRect()))
		{
			unitVector[i]->Render(GetMemDC());
		}
	}

	// ��� �ǹ� ������
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &buildingVector[i]->GetBuildingRect()))
		{
			buildingVector[i]->Render(GetMemDC());
		}
	}

	// �������� ���� ������
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetUnitKind() == LARVA)
		{
			unitVector[i]->RenderAirUint(GetMemDC());
		}
	}

	// ���� ���� �׸��� ������
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &airUnitVector[i]->GetUnitRect()))
		{
			airUnitVector[i]->RenderShadow(GetMemDC());
		}
	}

	// ���� ���� ������
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &airUnitVector[i]->GetUnitRect()))
		{
			airUnitVector[i]->Render(GetMemDC());
		}
	}

	// ���� �巡�� ������
	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		HBRUSH myBrush, oldBrush;
		HPEN myPen, oldPen;

		myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(GetMemDC(), myBrush);
		myPen = CreatePen(PS_SOLID, 2, RGB(0, 222, 0));
		oldPen = (HPEN)SelectObject(GetMemDC(), myPen);

		//Rectangle(GetMemDC(), leftPoint, topPoint, rightPoint, bottomPoint);
		Rectangle(GetMemDC(), dragRect.left, dragRect.top, dragRect.right, dragRect.bottom);
		
		SelectObject(GetMemDC(), oldBrush);
		DeleteObject(myBrush);
		SelectObject(GetMemDC(), oldPen);
		DeleteObject(myPen);
	}
	else
	{
		dragRect.left = m_ptMouse.x;
		dragRect.top = m_ptMouse.y;
		dragRect.right = m_ptMouse.x;
		dragRect.bottom = m_ptMouse.y;
		//dragRect.left = CAMERAMANAGER->GetCameraCenter().x + WINSIZEX;
		//dragRect.top = CAMERAMANAGER->GetCameraCenter().y + WINSIZEY;
		//dragRect.right = CAMERAMANAGER->GetCameraCenter().x + WINSIZEX;
		//dragRect.bottom = CAMERAMANAGER->GetCameraCenter().y + WINSIZEY;
	}

	// ������ Ÿ�� �׸���
	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		HBRUSH myBrush, oldBrush;
		HPEN myPen, oldPen;
		
		myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(GetMemDC(), myBrush);
		myPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(GetMemDC(), myPen);

		for (int i = 0; i < TILESIZE; i++)
		{
			if (IntersectRect(&tempRect, &cameraRect2, &_tileMap[i].rect))
			{
				Rectangle(GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].right, _tileMap[i].bottom);
			}
		}

		SelectObject(GetMemDC(), oldBrush);
		DeleteObject(myBrush);
		SelectObject(GetMemDC(), oldPen);
		DeleteObject(myPen);

	}

	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILESIZE; i++)
		{
			if (IntersectRect(&tempRect, &cameraRect2, &_tileMap[i].rect))
			{
				SetTextColor(GetMemDC(), RGB(255, 222, 222));
				sprintf_s(str, "(%d)", i);
				TextOut(GetMemDC(), _tileMap[i].left + CELL_WIDTH / 2 - 20, _tileMap[i].top + CELL_HEIGHT / 2 - 10, str, strlen(str));
			}
		}
	}

	// ���ֺ��ٴ� ���� �ְ� ���� UI���ٴ� �Ʒ��� �ִ� �ܼ� ������
	consoleImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	//Rectangle(GetMemDC(), commandRect.left, commandRect.top, commandRect.right, commandRect.bottom);
	
	HFONT myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "�������ü");
	HFONT oldFont = (HFONT)SelectObject(GetMemDC(), myFont);

	// �ܼ� ���� ����� UI������
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetIsClick())
		{
			buildingVector[i]->RenderUI(GetMemDC());
			break;
		}
	}
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetIsClick())
		{
			unitVector[i]->RenderUI(GetMemDC());
			break;
		}
	}
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (airUnitVector[i]->GetIsClick())
		{
			consoleImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);

			airUnitVector[i]->RenderUI(GetMemDC());
			break;
		}
	}
	
	SetTextColor(GetMemDC(), RGB(0, 222, 0));
	
	mineralImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	sprintf_s(str, "%d", mineral);
	TextOut(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + 35, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2 + 5, str, strlen(str));
	
	vespeneGasImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + WINSIZEX * 0.1, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	sprintf_s(str, "%d", vespeneGas);
	TextOut(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + WINSIZEX * 0.1 + 35, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2 + 5, str, strlen(str));
	
	populationImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + WINSIZEX * 0.1 + WINSIZEX * 0.1, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	sprintf_s(str, "%d/%d", currentPopulation, maxPopulation);
	TextOut(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + WINSIZEX * 0.1 + WINSIZEX * 0.1 + 35, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2 + 5, str, strlen(str));

	SelectObject(GetMemDC(), oldFont);
	DeleteObject(myFont);
}

void GameScene::LoadMap(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TAGTILE) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}

void GameScene::DrawTileMap()
{
	for (int i = 0; i < TILESIZE; i++)
	{
		if (IntersectRect(&tempRect, &cameraRect1, &_tileMap[i].rect))
		{
			if (_tileMap[i].tileKind != TILEKIND_NONE)
			{
				switch (_tileMap[i].tileKind)
				{
				case TILEKIND_BASETERRAIN:
					IMAGEMANAGER->FrameRender("BaseMap", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_TERRAIN:
					IMAGEMANAGER->FrameRender("MapTile1", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_CREEP:
					IMAGEMANAGER->FrameRender("MapTile1", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_STAIR:
					IMAGEMANAGER->FrameRender("MapTile2", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_STAIRBLOCK:
					IMAGEMANAGER->FrameRender("MapTile2", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				}
			}
		}
	}
}
