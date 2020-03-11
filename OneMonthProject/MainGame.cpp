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
	// ���ҽ� Ŭ���� ����
	resource = new ResourceCollection;
	resource->Init();

	// �� Ŭ���� ����
	map = new MapToolScene;
	SCENEMANAGER->AddScene("MapTool", map);

	// ����� �¾�
	SUBWIN->SetMap(map);

	// ���� ���� Scene
	SCENEMANAGER->AddScene("GameScene", new GameScene);

	// A*�׽�Ʈ
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
	//��� ��Ʈ��
	//PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->GetCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================
	
	SCENEMANAGER->Render();



	//===================================================
	//������� ������ HDC�� �׸���.(�ǵ帮������.)
	//this->GetBackBuffer()->Render(GetHDC(), 0, 0);
	CAMERAMANAGER->Render(this->GetBackBuffer());
	this->GetBackBuffer()->Render(GetHDC(), 0, 0, CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);

}