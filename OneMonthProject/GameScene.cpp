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
	PLAYERMANAGER->Init();

	// �ʱ� ��ó�� ����
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2 - 400, WINSIZEY / 2}));
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2, WINSIZEY / 2}));
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2 + 400, WINSIZEY / 2}));

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

	if (PLAYERMANAGER->GetTempVector().size() > 0)
	{
		while (PLAYERMANAGER->GetTempVector().size() > 0)
		{
			unitVector.push_back(PLAYERMANAGER->ReturnUnitVector());
		}
	}

	// ������ �����ƴٸ� ���Ϳ��� �����
	for (int i = 0; i < selectVector.size(); i++)
	{
		if (selectVector[i]->GetIsClick() == false)
		{
			selectVector.erase(selectVector.begin() + i);
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

	COLLISIONMANAGER->SameVectorCollision(unitVector);

	
	//if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	//{
	//	leftPoint = m_ptMouse.x;
	//	topPoint = m_ptMouse.y;
	//}
	//if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
	//{
	//	rightPoint = m_ptMouse.x;
	//	bottomPoint = m_ptMouse.y;
	//}

	PLAYERMANAGER->SetInputCommand(false);
}

void GameScene::Render()
{
	mainMap->Render();

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
		buildingVector[i]->Render(GetMemDC());
	}

	// ��� ���� ������
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->Render(GetMemDC());
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

	//Rectangle(GetMemDC(), leftPoint, topPoint, rightPoint, bottomPoint);

}
