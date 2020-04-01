#include "stdafx.h"
#include "MenuScene.h"


MenuScene::MenuScene()
{
}


MenuScene::~MenuScene()
{
}

HRESULT MenuScene::Init()
{
	backGroundImage = IMAGEMANAGER->FindImage("background");
	
	singlePlay = IMAGEMANAGER->FindImage("singlePlay");
	singlePlayRect = RectMake(50, 50, singlePlay->GetFrameWidth(), singlePlay->GetFrameHeight());
	singlePlayOverlay = IMAGEMANAGER->FindImage("singlePlayOverlay");
	singlePlayOverlayRect = RectMake(100, 200, singlePlayOverlay->GetFrameWidth(), singlePlayOverlay->GetFrameHeight());

	mapTool = IMAGEMANAGER->FindImage("mapTool");
	mapToolRect = RectMake(750, 50, mapTool->GetFrameWidth(), mapTool->GetFrameHeight());
	mapToolOverlay = IMAGEMANAGER->FindImage("mapToolOverlay");
	mapToolOverlayRect = RectMake(790, 85, mapToolOverlay->GetFrameWidth(), mapToolOverlay->GetFrameHeight());

	exit = IMAGEMANAGER->FindImage("exit");
	exitRect = RectMake(630, 520, exit->GetFrameWidth(), exit->GetFrameHeight());
	exitOverlay = IMAGEMANAGER->FindImage("exitOverlay");
	exitOverlayRect = RectMake(660, 520, exitOverlay->GetFrameWidth(), exitOverlay->GetFrameHeight());



	return S_OK;
}

void MenuScene::Release()
{
}

void MenuScene::Update()
{
	if (PtInRect(&singlePlayRect, m_ptMouse) || PtInRect(&singlePlayOverlayRect, m_ptMouse))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		{
			SCENEMANAGER->ChangeScene("GameScene");
		}
	}
	if (PtInRect(&mapToolRect, m_ptMouse) || PtInRect(&mapToolOverlayRect, m_ptMouse))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		{
			SCENEMANAGER->ChangeScene("MapTool");
		}
	}
	if (PtInRect(&exitRect, m_ptMouse) || PtInRect(&exitOverlayRect, m_ptMouse))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		{
			PostQuitMessage(0);
		}
	}


	singlePlayframeCount++;
	singlePlay->SetFrameY(singlePlayframeIndexY);
	if (singlePlayframeCount % 5 == 0)
	{
		singlePlayframeCount = 0;
		if (singlePlayframeIndexX >= singlePlay->GetMaxFrameX())
		{
			singlePlayframeIndexX = 0;
		}
		singlePlay->SetFrameX(singlePlayframeIndexX);
		singlePlayframeIndexX++;
	}	

	singlePlayOverlayframeCount++;
	singlePlayOverlay->SetFrameY(singlePlayOverlayframeIndexY);
	if (singlePlayOverlayframeCount % 5 == 0)
	{
		singlePlayOverlayframeCount = 0;
		if (singlePlayOverlayframeIndexX >= singlePlayOverlay->GetMaxFrameX())
		{
			singlePlayOverlayframeIndexX = 0;
		}
		singlePlayOverlay->SetFrameX(singlePlayOverlayframeIndexX);
		singlePlayOverlayframeIndexX++;
	}
	
	mapToolframeCount++;
	mapTool->SetFrameY(mapToolframeIndexY);
	if (mapToolframeCount % 5 == 0)
	{
		mapToolframeCount = 0;
		if (mapToolframeIndexX >= mapTool->GetMaxFrameX())
		{
			mapToolframeIndexX = 0;
		}
		mapTool->SetFrameX(mapToolframeIndexX);
		mapToolframeIndexX++;
	}

	mapToolOverlayframeCount++;
	mapToolOverlay->SetFrameY(mapToolOverlayframeIndexY);
	if (mapToolOverlayframeCount % 5 == 0)
	{
		mapToolOverlayframeCount = 0;
		if (mapToolOverlayframeIndexX >= mapToolOverlay->GetMaxFrameX())
		{
			mapToolOverlayframeIndexX = 0;
		}
		mapToolOverlay->SetFrameX(mapToolOverlayframeIndexX);
		mapToolOverlayframeIndexX++;
	}
	
	exitframeCount++;
	exit->SetFrameY(exitframeIndexY);
	if (exitframeCount % 5 == 0)
	{
		exitframeCount = 0;
		if (exitframeIndexX >= exit->GetMaxFrameX())
		{
			exitframeIndexX = 0;
		}
		exit->SetFrameX(exitframeIndexX);
		exitframeIndexX++;
	}

	exitOverlayframeCount++;
	exitOverlay->SetFrameY(exitOverlayframeIndexY);
	if (exitOverlayframeCount % 5 == 0)
	{
		exitOverlayframeCount = 0;
		if (exitOverlayframeIndexX >= exitOverlay->GetMaxFrameX())
		{
			exitOverlayframeIndexX = 0;
		}
		exitOverlay->SetFrameX(exitOverlayframeIndexX);
		exitOverlayframeIndexX++;
	}

}

void MenuScene::Render()
{
	backGroundImage->Render(GetMemDC(), 0, 0);

	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		Rectangle(GetMemDC(), singlePlayRect.left, singlePlayRect.top, singlePlayRect.right, singlePlayRect.bottom);
		Rectangle(GetMemDC(), singlePlayOverlayRect.left, singlePlayOverlayRect.top, singlePlayOverlayRect.right, singlePlayOverlayRect.bottom);
		Rectangle(GetMemDC(), mapToolRect.left, mapToolRect.top, mapToolRect.right, mapToolRect.bottom);
		Rectangle(GetMemDC(), mapToolOverlayRect.left, mapToolOverlayRect.top, mapToolOverlayRect.right, mapToolOverlayRect.bottom);
		Rectangle(GetMemDC(), exitRect.left, exitRect.top, exitRect.right, exitRect.bottom);
		Rectangle(GetMemDC(), exitOverlayRect.left, exitOverlayRect.top, exitOverlayRect.right, exitOverlayRect.bottom);
	}

	if (PtInRect(&singlePlayOverlayRect, m_ptMouse) || PtInRect(&singlePlayRect, m_ptMouse))
	{
		singlePlayOverlay->FrameRender(GetMemDC(), singlePlayOverlayRect.left, singlePlayOverlayRect.top, singlePlayOverlayframeIndexX, singlePlayOverlayframeIndexY);
	}
	singlePlay->FrameRender(GetMemDC(), singlePlayRect.left, singlePlayRect.top, singlePlayframeIndexX, singlePlayframeIndexY);

	mapTool->FrameRender(GetMemDC(), mapToolRect.left, mapToolRect.top, mapToolframeIndexX, mapToolframeIndexY);
	if (PtInRect(&mapToolOverlayRect, m_ptMouse) || PtInRect(&mapToolRect, m_ptMouse))
	{
		mapToolOverlay->FrameRender(GetMemDC(), mapToolOverlayRect.left, mapToolOverlayRect.top, mapToolOverlayframeIndexX, mapToolOverlayframeIndexY);
	}

	exit->FrameRender(GetMemDC(), exitRect.left, exitRect.top, exitframeIndexX, exitframeIndexY);
	if (PtInRect(&exitOverlayRect, m_ptMouse) || PtInRect(&exitRect, m_ptMouse))
	{
		exitOverlay->FrameRender(GetMemDC(), exitOverlayRect.left, exitOverlayRect.top, exitOverlayframeIndexX, exitOverlayframeIndexY);
	}

}
