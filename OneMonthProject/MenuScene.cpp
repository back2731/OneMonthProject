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

	singlePlayText = IMAGEMANAGER->FindImage("singlePlayText");
	singlePlay = IMAGEMANAGER->FindImage("singlePlay");
	singlePlayRect = RectMake(50, 50, singlePlay->GetFrameWidth(), singlePlay->GetFrameHeight());
	singlePlayOverlay = IMAGEMANAGER->FindImage("singlePlayOverlay");
	singlePlayOverlayRect = RectMake(100, 200, singlePlayOverlay->GetFrameWidth(), singlePlayOverlay->GetFrameHeight() - 200);

	mapToolText = IMAGEMANAGER->FindImage("mapToolText");
	mapTool = IMAGEMANAGER->FindImage("mapTool");
	mapToolRect = RectMake(750, 50, mapTool->GetFrameWidth(), mapTool->GetFrameHeight());
	mapToolOverlay = IMAGEMANAGER->FindImage("mapToolOverlay");
	mapToolOverlayRect = RectMake(790, 85, mapToolOverlay->GetFrameWidth(), mapToolOverlay->GetFrameHeight());

	exitText = IMAGEMANAGER->FindImage("exitText");
	exit = IMAGEMANAGER->FindImage("exit");
	exitRect = RectMake(630, 520, exit->GetFrameWidth(), exit->GetFrameHeight());
	exitOverlay = IMAGEMANAGER->FindImage("exitOverlay");
	exitOverlayRect = RectMake(660, 520, exitOverlay->GetFrameWidth(), exitOverlay->GetFrameHeight());

	multiPlayText = IMAGEMANAGER->FindImage("multiPlayText");
	multiPlay = IMAGEMANAGER->FindImage("multiPlay");
	multiPlayTail = IMAGEMANAGER->FindImage("multiPlayTail");
	multiPlayRect = RectMake(50, 350, multiPlay->GetFrameWidth(), multiPlay->GetFrameHeight());
	multiPlayOverlay = IMAGEMANAGER->FindImage("multiPlayOverlay");
	multiPlayOverlayRect = RectMake(90, 370, multiPlayOverlay->GetFrameWidth(), multiPlayOverlay->GetFrameHeight());


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

	multiPlayframeCount++;
	multiPlay->SetFrameY(multiPlayframeIndexY);
	if (multiPlayframeCount % 5 == 0)
	{
		multiPlayframeCount = 0;
		if (multiPlayframeIndexX >= multiPlay->GetMaxFrameX())
		{
			multiPlayframeIndexX = 0;
		}
		multiPlay->SetFrameX(multiPlayframeIndexX);
		multiPlayframeIndexX++;
	}

	multiPlayOverlayframeCount++;
	multiPlayOverlay->SetFrameY(multiPlayOverlayframeIndexY);
	if (multiPlayOverlayframeCount % 5 == 0)
	{
		multiPlayOverlayframeCount = 0;
		if (multiPlayOverlayframeIndexX >= multiPlayOverlay->GetMaxFrameX())
		{
			multiPlayOverlayframeIndexX = 0;
		}
		multiPlayOverlay->SetFrameX(multiPlayOverlayframeIndexX);
		multiPlayOverlayframeIndexX++;
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
		Rectangle(GetMemDC(), multiPlayRect.left, multiPlayRect.top, multiPlayRect.right, multiPlayRect.bottom);
		Rectangle(GetMemDC(), multiPlayOverlayRect.left, multiPlayOverlayRect.top, multiPlayOverlayRect.right, multiPlayOverlayRect.bottom);
	}

	if (PtInRect(&singlePlayOverlayRect, m_ptMouse) || PtInRect(&singlePlayRect, m_ptMouse))
	{
		singlePlayOverlay->FrameRender(GetMemDC(), singlePlayOverlayRect.left, singlePlayOverlayRect.top, singlePlayOverlayframeIndexX, singlePlayOverlayframeIndexY);
	}
	singlePlay->FrameRender(GetMemDC(), singlePlayRect.left, singlePlayRect.top, singlePlayframeIndexX, singlePlayframeIndexY);
	singlePlayText->Render(GetMemDC(), 330, 290);
  
	mapTool->FrameRender(GetMemDC(), mapToolRect.left, mapToolRect.top, mapToolframeIndexX, mapToolframeIndexY);
	if (PtInRect(&mapToolOverlayRect, m_ptMouse) || PtInRect(&mapToolRect, m_ptMouse))
	{
		mapToolOverlay->FrameRender(GetMemDC(), mapToolOverlayRect.left, mapToolOverlayRect.top, mapToolOverlayframeIndexX, mapToolOverlayframeIndexY);
	}
	mapToolText->Render(GetMemDC(), 850, 335);

	exit->FrameRender(GetMemDC(), exitRect.left, exitRect.top, exitframeIndexX, exitframeIndexY);
	if (PtInRect(&exitOverlayRect, m_ptMouse) || PtInRect(&exitRect, m_ptMouse))
	{
		exitOverlay->FrameRender(GetMemDC(), exitOverlayRect.left, exitOverlayRect.top, exitOverlayframeIndexX, exitOverlayframeIndexY);
	}
	exitText->Render(GetMemDC(), 800, 520);

	multiPlay->FrameRender(GetMemDC(), multiPlayRect.left, multiPlayRect.top, multiPlayframeIndexX, multiPlayframeIndexY);
	if (PtInRect(&multiPlayOverlayRect, m_ptMouse) || PtInRect(&multiPlayRect, m_ptMouse))
	{
		multiPlayOverlay->FrameRender(GetMemDC(), multiPlayOverlayRect.left, multiPlayOverlayRect.top, multiPlayOverlayframeIndexX, multiPlayOverlayframeIndexY);
	}
	multiPlayTail->Render(GetMemDC(), 345, 665);
	multiPlayText->Render(GetMemDC(), 400, 475);

	sprintf_s(str, "x : %d", m_ptMouse.x);
	TextOut(GetMemDC(), 0, 0, str, strlen(str));
	sprintf_s(str, "y : %d", m_ptMouse.y);
	TextOut(GetMemDC(), 70, 0, str, strlen(str));

}
