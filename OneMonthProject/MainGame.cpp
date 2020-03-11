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
	// 리소스 클래스 생성
	resource = new ResourceCollection;
	resource->Init();

	// 맵 클래스 생성
	map = new MapToolScene;
	SCENEMANAGER->AddScene("MapTool", map);

	// 서브맵 셋업
	SUBWIN->SetMap(map);

	// 실제 게임 Scene
	SCENEMANAGER->AddScene("GameScene", new GameScene);

	// A*테스트
	SCENEMANAGER->AddScene("aStar", new aStarScene);


	SCENEMANAGER->ChangeScene("GameScene");

	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
	SAFE_DELETE(map);
	SAFE_DELETE(resource);
}

void MainGame::Update()
{
	GameNode::Update();

	CAMERAMANAGER->MoveCamera();
	ANIMATIONMANAGER->Update();
	SCENEMANAGER->Update();


}

void MainGame::Render(/*HDC hdc*/)
{
	//흰색 비트맵
	//PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->GetCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================
	
	SCENEMANAGER->Render();



	//===================================================
	//백버퍼의 내용을 HDC에 그린다.(건드리지말것.)
	//this->GetBackBuffer()->Render(GetHDC(), 0, 0);
	CAMERAMANAGER->Render(this->GetBackBuffer());
	this->GetBackBuffer()->Render(GetHDC(), 0, 0, CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);

}