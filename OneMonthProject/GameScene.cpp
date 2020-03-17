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

	// 초기 해처리 생성
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2 - 400, WINSIZEY / 2}));
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2, WINSIZEY / 2}));
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2 + 400, WINSIZEY / 2}));

	// 해당 건물이 해처리라면 라바를 세팅해준다
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

	// 모든 건물 업데이트
	for (int i = 0; i < buildingVector.size(); i++)
	{
		buildingVector[i]->Update();
	}
	// 모든 유닛 업데이트
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->Update();
	}
	
	// 해당 건물을 클릭 했을 때 상태를 변경해주는 부분
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

	// 해당 유닛을 클릭 했을 때 상태를 변경해주는 부분
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
				// 선택된 유닛을 셀렉트 벡터에 담는다
				if (unitVector[i]->GetIsClick())
				{
					selectVector.push_back(unitVector[i]);
				}
			}
		}
	}

	// 해처리(레어, 하이브)에서 셀렉트 라바를 눌렀을 때
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
		unitVector.push_back(PLAYERMANAGER->ReturnUnitVector());
	}

	// 선택이 해제됐다면 벡터에서 지운다
	for (int i = 0; i < selectVector.size(); i++)
	{
		if(selectVector[i]->GetIsClick() == false)
		{
			selectVector.erase(selectVector.begin() + i); 
		}
	}

	// 변신중이라면 삭제
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetUnitKind() == LARVA)
		{
			if (unitVector[i]->GetIsTransform())
			{
				unitVector.erase(unitVector.begin() + i);
			}
		}
	}
}

void GameScene::Render()
{
	mainMap->Render();

	// 렉트 테스트용
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

	// 모든 건물 렌더링
	for (int i = 0; i < buildingVector.size(); i++)
	{
		buildingVector[i]->Render(GetMemDC());
	}

	// 모든 유닛 렌더링
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->Render(GetMemDC());
	}

	// 유닛보다는 위에 있고 유닛 UI보다는 아래에 있는 콘솔 렌더링
	IMAGEMANAGER->FindImage("ZurgConsole")->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	
	// 콘솔 위에 띄워질 UI렌더링
	for (int i = 0; i < buildingVector.size(); i++)
	{
		buildingVector[i]->RenderUI(GetMemDC());
	}
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->RenderUI(GetMemDC());
	}

}
