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

	// 맵툴용 이미지들
	IMAGEMANAGER->AddFrameImage("MapTile1", "images/MapTile/Tile001.bmp",
		0, 0, 32 * 16 * 2, 32 * 17 * 2, 16, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("계단", "images/MapTile/계단.bmp",
		0, 0, 32 * 16 * 2, 32 * 17 * 2, 16, 17, true, RGB(255, 0, 255));	
	IMAGEMANAGER->AddFrameImage("MapTile3", "images/MapTile/test1.bmp",
		0, 0, 32 * 16 * 2, 32 * 17 * 2, 16, 17, true, RGB(255, 0, 255));

	// 실제 게임 Scene
	SCENEMANAGER->AddScene("GameScene", new GameScene);

	// A*테스트
	SCENEMANAGER->AddScene("aStar", new aStarScene);

	MapToolScene* map = new MapToolScene;
	SCENEMANAGER->AddScene("MapTool", map);

	SUBWIN->SetIsoMap(map);


	SCENEMANAGER->ChangeScene("GameScene");

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