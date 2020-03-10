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

	test1 = IMAGEMANAGER->AddFrameImage("test", "images/MapTile/Hatchery.bmp", 1152*1.5, 160*1.5, 6, 1, true, RGB(0, 222, 0));
	ANIMATIONMANAGER->AddAnimation("testAni", "test", 1, 5, 15, false, true);
	testAni = ANIMATIONMANAGER->FindAnimation("testAni");
	testRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, test1->GetFrameWidth(), test1->GetFrameHeight());

	return S_OK;
}

void GameScene::Release()
{
	SAFE_DELETE(mainMap);
}

void GameScene::Update()
{
	mainMap->Update();
	testAni = ANIMATIONMANAGER->FindAnimation("testAni");
	ANIMATIONMANAGER->Start("testAni");
}

void GameScene::Render()
{
	mainMap->Render();
	//Rectangle(GetMemDC(), testRect.left, testRect.top, testRect.right, testRect.bottom);
	//test1->FrameRender(GetMemDC(), testRect.left, testRect.top);
	test1->AniRender(GetMemDC(), testRect.left, testRect.top, testAni);
}
