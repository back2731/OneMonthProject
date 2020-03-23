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
	mainMap = new MainMap;
	mainMap->Init();
	LoadMap(0);
	buildingVector.reserve(1000);
	unitVector.reserve(1000);
	selectVector.reserve(50);
	// �ʱ� ��ó�� ����
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2, WINSIZEY / 2 + 500}));
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2, WINSIZEY / 2 }));
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2, WINSIZEY / 2 + 800}));
	
	// �ش� �ǹ��� ��ó����� ��ٸ� �������ش�
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetBuildKind() == HATCHERY)
		{
			unitVector.push_back(UNITMANAGER->CreateLarva({ buildingVector[i]->GetBuildingRectX() - 70, buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 1));
			unitVector.push_back(UNITMANAGER->CreateLarva({ buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 2));
			unitVector.push_back(UNITMANAGER->CreateLarva({ buildingVector[i]->GetBuildingRectX() + 70, buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 3));
			
			buildingVector[i]->SetCurrentLarva(LARVAMAX);
		}
	}
	return S_OK;
}

void GameScene::Release()
{
	SAFE_DELETE(mainMap);
}

void GameScene::Update()
{
	ShowCursor(false);

	commandRect = RectMake(CAMERAMANAGER->GetCameraCenter().x + 335, CAMERAMANAGER->GetCameraCenter().y + 225, 250, 250);
	cameraRect = RectMake(CAMERAMANAGER->GetCameraXY().x - WINSIZEX, CAMERAMANAGER->GetCameraXY().y - WINSIZEY, WINSIZEX * 2, WINSIZEY * 2);

	mainMap->Update();
	PLAYERMANAGER->Update();

	// ��� �ǹ� ������Ʈ
	for (int i = 0; i < buildingVector.size(); i++)
	{
		buildingVector[i]->Update();
	}
	// ��� ���� ������Ʈ
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->Update();
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
				}
			}
		}
	}

	// �ش� ������ Ŭ�� ���� �� ���¸� �������ִ� �κ�
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
				}
				// ���õ� ������ ����Ʈ ���Ϳ� ��´�
				if (unitVector[i]->GetIsClick())
				{
					selectVector.push_back(unitVector[i]);
				}
			}
		}
	}

	// ��ó��(����, ���̺�)���� ����Ʈ ��ٸ� ������ ��
	if (PLAYERMANAGER->GetSelectLarvaValue())
	{
		for (int i = 0; i < buildingVector.size(); i++)
		{
			buildingVector[i]->SetIsClick(false);
		}

		for (int i = 0; i < unitVector.size(); i++)
		{
			if (unitVector[i]->GetHatcheryX() == PLAYERMANAGER->GetSaveX() && unitVector[i]->GetHatcheryY() == PLAYERMANAGER->GetSaveY())
			{
				unitVector[i]->SetIsClick(true);
				selectVector.push_back(unitVector[i]);
			}
		}
		PLAYERMANAGER->SetSelectLarva(false);
	}

	// ����� ������ ���� ���Ͱ� 0���� Ŭ�� �Լ��� ���� �����´�.
	if (PLAYERMANAGER->GetTempVector().size() > 0)
	{
		while (PLAYERMANAGER->GetTempVector().size() > 0)
		{
			unitVector.push_back(PLAYERMANAGER->ReturnUnitVector());
		}
	}


	// ���¸� ��ġ�� ���� �� ��ó�� ���� ��� �� ����
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetUnitKind() == LARVA)
		{
			if (unitVector[i]->GetIsTransform())
			{
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

	// ��� �ڵ� ���� ���
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetCurrentLarva() < LARVAMAX)
		{
			count++;
			if (count % 200 == 0)
			{
				unitVector.push_back(UNITMANAGER->CreateLarva({ buildingVector[i]->GetBuildingRectX() - 70 + (70 * RND->GetInt(2)), buildingVector[i]->GetBuildingRect().bottom + 25 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 1));
				buildingVector[i]->SetCurrentLarva(+1);
			}
		}
	}

	// ���ְ��� �浹ó�� �Լ�
	COLLISIONMANAGER->SameVectorCollision(unitVector);

	// ����� ����Ǹ� false�� �����ϴ� �Լ�
	PLAYERMANAGER->SetInputCommandTransDrone(false);
	PLAYERMANAGER->SetInputCommandMove(false);

	// �巡�� ��ɹ�
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		dragRect.left = m_ptMouse.x;
		dragRect.top = m_ptMouse.y;
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

	// �巡�׵� ���� ���� ��ɹ�
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &dragRect, &unitVector[i]->GetUnitRect()))
		{
			unitVector[i]->SetIsClick(true);
			selectVector.push_back(unitVector[i]);
		}
	}

	//// ���ֵ��� �������Ͻÿ��� �ǹ������� false���ش�.
	//if (selectVector.size() > 0) 
	//{
	//	for (int i = 0; i < buildingVector.size(); i++)
	//	{
	//		buildingVector[i]->SetIsClick(false);
	//	}
	//}
	for (int i = 0; i < TILESIZE; i++)
	{
		for (int j = 0; j < buildingVector.size(); j++)
		{
			if (_tileMap[i].block == true) continue;
			{
				if (IntersectRect(&tempRect, &_tileMap[i].rect, &buildingVector[j]->GetBuildingRect()))
				{
					_tileMap[i].block = true;
					PLAYERMANAGER->SetBlockTile(i);
				}
			}
		}
	}
}

void GameScene::Render()
{
	mainMap->Render(GetMemDC());

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
	}

	// ��� �ǹ� ������
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect, &buildingVector[i]->GetBuildingRect()))
		{
			buildingVector[i]->Render(GetMemDC());
		}
	}

	// ��� ���� ������
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect, &unitVector[i]->GetUnitRect()))
		{
			unitVector[i]->Render(GetMemDC());
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
		dragRect.left = CAMERAMANAGER->GetCameraCenter().x + WINSIZEX;
		dragRect.top = CAMERAMANAGER->GetCameraCenter().y + WINSIZEY;
		dragRect.right = CAMERAMANAGER->GetCameraCenter().x + WINSIZEX;
		dragRect.bottom = CAMERAMANAGER->GetCameraCenter().y + WINSIZEY;
	}

	// ���ֺ��ٴ� ���� �ְ� ���� UI���ٴ� �Ʒ��� �ִ� �ܼ� ������
	IMAGEMANAGER->FindImage("ZurgConsole")->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	
	// �ܼ� ���� ����� UI������
	for (int i = 0; i < buildingVector.size(); i++)
	{
		buildingVector[i]->RenderUI(GetMemDC());
	}
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->RenderUI(GetMemDC());
	}
}

void GameScene::LoadMap(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TAGTILE) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}
