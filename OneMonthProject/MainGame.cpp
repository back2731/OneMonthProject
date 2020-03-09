#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	GameNode::Init(true);
	
	// A*테스트
	SCENEMANAGER->AddScene("aStar", new aStarScene);

	MapToolScene* map = new MapToolScene;
	SCENEMANAGER->AddScene("MapTool", map);

	SUBWIN->SetIsoMap(map);

	// 게임씬에서 필요한 매니저들 초기화.
	OBJECTPOOL->Init();

	SCENEMANAGER->ChangeScene("aStar");

	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
}

void MainGame::Update()
{
	GameNode::Update();

	SCENEMANAGER->Update();

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT) && CAMERAMANAGER->GetCameraXY().x > 0)
	{
		CAMERAMANAGER->SetCameraCenter(PointMake(CAMERAMANAGER->GetCameraCenter().x - 52, CAMERAMANAGER->GetCameraCenter().y));
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) && CAMERAMANAGER->GetCameraXY().x < 52*62)
	{
		CAMERAMANAGER->SetCameraCenter(PointMake(CAMERAMANAGER->GetCameraCenter().x + 52, CAMERAMANAGER->GetCameraCenter().y));
	}

	if (KEYMANAGER->IsStayKeyDown(VK_UP) && CAMERAMANAGER->GetCameraXY().y > 0)
	{
		CAMERAMANAGER->SetCameraCenter(PointMake(CAMERAMANAGER->GetCameraCenter().x, CAMERAMANAGER->GetCameraCenter().y - 52));
	}

	if (KEYMANAGER->IsStayKeyDown(VK_DOWN) && CAMERAMANAGER->GetCameraXY().y < 52*38)
	{
		CAMERAMANAGER->SetCameraCenter(PointMake(CAMERAMANAGER->GetCameraCenter().x, CAMERAMANAGER->GetCameraCenter().y + 52));
	}
//#ifdef SUBWINOPEN
//
//	SUBWIN->Update();
//#endif // SUBWINOPEN
}

void MainGame::Render(/*HDC hdc*/)
{
	//흰색 비트맵
	//PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->GetCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================

	SCENEMANAGER->Render();
	//#ifdef SUBWINOPEN
	//	SUBWIN->Render();
	//#endif // SUBWINOPEN
	TIMEMANAGER->Render(GetMemDC());

	//===================================================
	//백버퍼의 내용을 HDC에 그린다.(건드리지말것.)
	//this->GetBackBuffer()->Render(GetHDC(), 0, 0);
	CAMERAMANAGER->Render(this->GetBackBuffer());
	this->GetBackBuffer()->Render(GetHDC(), 0, 0, CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);

}