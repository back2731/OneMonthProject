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
	BUILDMANAGER->Init();
	UNITMANAGER->Init();

	m_MyBuilding.push_back(BUILDMANAGER->CreateHatchery({ WINSIZEX / 2, WINSIZEY / 2}));

	return S_OK;
}

void GameScene::Release()
{
	SAFE_DELETE(mainMap);
}

void GameScene::Update()
{
	mainMap->Update();

	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		m_MyBuilding.push_back(BUILDMANAGER->CreateHatchery(m_ptMouse));
	}

	BUILDMANAGER->Update();
	UNITMANAGER->Update();
	for (auto& building : m_MyBuilding)
	{
		building->Update();
	}
}

void GameScene::Render()
{
	mainMap->Render();
	BUILDMANAGER->Render(GetMemDC());
	UNITMANAGER->Render(GetMemDC());

	for (auto& building : m_MyBuilding)
	{
		building->Render(GetMemDC());
	}
}
