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

	return S_OK;
}

void GameScene::Release()
{
	SAFE_DELETE(mainMap);
}

void GameScene::Update()
{
	mainMap->Update();
	BUILDMANAGER->Update();
	UNITMANAGER->Update();
}

void GameScene::Render()
{
	mainMap->Render();
	BUILDMANAGER->Render(GetMemDC());
	UNITMANAGER->Render(GetMemDC());
}
