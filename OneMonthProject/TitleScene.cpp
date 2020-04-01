#include "stdafx.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

HRESULT TitleScene::Init()
{
	titleImage = IMAGEMANAGER->FindImage("title");
	return S_OK;
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{
	ShowCursor(false);
	loadingCount++;

	if (loadingCount % 100 == 0)
	{
		SCENEMANAGER->ChangeScene("MenuScene");
	}
}

void TitleScene::Render()
{
	titleImage->Render(GetMemDC(), 0, 0);
}
