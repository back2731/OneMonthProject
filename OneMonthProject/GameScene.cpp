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

	// 檬扁 秦贸府 积己
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2, WINSIZEY / 2}));
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2 - 400, WINSIZEY / 2}));
	buildingVector.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2 + 400, WINSIZEY / 2}));

	return S_OK;
}

void GameScene::Release()
{
	SAFE_DELETE(mainMap);
}

void GameScene::Update()
{
	mainMap->Update();

	for (auto& building : buildingVector)
	{
		building->Update();
	}
	
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (PtInRect(&buildingVector[i]->GetBuildingRect(), m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON) && !buildingVector[i]->GetIsClick())
			{
				for (int j = 0; j < buildingVector.size(); j++)
				{
					buildingVector[j]->SetIsClick(false);
					buildingVector[i]->SetIsClick(true);
				}
			}
		}
	}
}

void GameScene::Render()
{
	mainMap->Render();

	for (auto& building : buildingVector)
	{
		building->Render(GetMemDC());
	}
	sprintf_s(str, "count :  %d", count);
	TextOut(GetMemDC(), 800, 0, str, strlen(str));

}
