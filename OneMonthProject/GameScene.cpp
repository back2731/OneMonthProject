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

	return S_OK;
}

void GameScene::Release()
{
	SAFE_DELETE(mainMap);
}

void GameScene::Update()
{

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT) && CAMERAMANAGER->GetCameraXY().x > 0)
	{
		CAMERAMANAGER->SetCameraCenter(PointMake(CAMERAMANAGER->GetCameraCenter().x - 100, CAMERAMANAGER->GetCameraCenter().y));
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) && CAMERAMANAGER->GetCameraXY().x < 32 * 100)
	{
		CAMERAMANAGER->SetCameraCenter(PointMake(CAMERAMANAGER->GetCameraCenter().x + 100, CAMERAMANAGER->GetCameraCenter().y));
	}

	if (KEYMANAGER->IsStayKeyDown(VK_UP) && CAMERAMANAGER->GetCameraXY().y > 0)
	{
		CAMERAMANAGER->SetCameraCenter(PointMake(CAMERAMANAGER->GetCameraCenter().x, CAMERAMANAGER->GetCameraCenter().y - 100));
	}

	if (KEYMANAGER->IsStayKeyDown(VK_DOWN) && CAMERAMANAGER->GetCameraXY().y < 32*100)
	{
		CAMERAMANAGER->SetCameraCenter(PointMake(CAMERAMANAGER->GetCameraCenter().x, CAMERAMANAGER->GetCameraCenter().y + 100));
	}


	mainMap->Update();
}

void GameScene::Render()
{
	mainMap->Render();
}
