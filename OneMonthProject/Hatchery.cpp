#include "stdafx.h"
#include "Hatchery.h"


Hatchery::Hatchery()
{
}


Hatchery::~Hatchery()
{
}

Hatchery::Hatchery(int _playerNumber, POINT buildXY)
{
	progressBar = new ProgressBar;

	currentLarva = 0;

	buildStatus.buidKind = HATCHERY;

	buildStatus.playerNumber = _playerNumber;

	buildStatus.buildingMaxHp = 1250;
	buildStatus.buildingCurrentHp = 1000;
	buildStatus.buildingAtk = 0;
	buildStatus.buildingDef = 1;
	buildStatus.buildTime = 120;

	buildStatus.buildingMineralPrice = 300;
	buildStatus.buildingGasPrice = 0;

	buildStatus.buildImage = IMAGEMANAGER->FindImage("Hatchery");
	buildStatus.buildingSelectImage = IMAGEMANAGER->FindImage("4X3");
	buildStatus.buildingWireFrame = IMAGEMANAGER->FindImage("HatcheryWirefram");

	buildStatus.buildRect = RectMakeCenter(buildXY.x, buildXY.y, buildStatus.buildImage->GetFrameWidth(), buildStatus.buildImage->GetFrameHeight());
	buildStatus.buildRectX = buildStatus.buildRect.left + (buildStatus.buildRect.right - buildStatus.buildRect.left) / 2;
	buildStatus.buildRectY = buildStatus.buildRect.top + (buildStatus.buildRect.bottom - buildStatus.buildRect.top) / 2;

	buildStatus.frameCount = 0;
	buildStatus.frameIndexX = 0;
	buildStatus.frameIndexY = 0;
	
	isClick = false;

	progressBar->Init("images/UI/ZurgProgressFront.bmp", "images/UI/ZurgProgressBack.bmp", buildStatus.buildRect.left, buildStatus.buildRect.bottom, 107 * 2, 9 * 2);

	// 명령 슬롯 생성
	SetCommandSlot(SLOT1, new SelectLarva);
	SetCommandSlot(SLOT2, new SetRallyPoint);
	SetCommandSlot(SLOT3, new EvolveBurrow);
	SetCommandSlot(SLOT7, new LairRequires);
}

HRESULT Hatchery::Init()
{
	return S_OK;
}

void Hatchery::Release()
{
	SAFE_DELETE(progressBar);
}

void Hatchery::Update()
{
	// 해처리 애니메이션 프레임 업데이트
	PlayAnimation();

	// 해당 객체가 클릭 되었을 때
	if (isClick)
	{
		// 명령 컨트롤 업데이트
		if (PtInRect(&commandRect[SLOT1], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				PLAYERMANAGER->SetSelectLarva(true);
				PLAYERMANAGER->SetXY(buildStatus.buildRectX, buildStatus.buildRectY);
			}						 
		}
	}

	// 슬롯 위치 카메라 반영
	SetCommandRect();

	progressBar->SetGauge(buildStatus.buildingCurrentHp, buildStatus.buildingMaxHp);
}

void Hatchery::Render(HDC hdc)
{	
	// 해당 객체가 클릭 되었을 때
	if (isClick)
	{  
		buildStatus.buildingSelectImage->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingSelectImage->GetWidth() / 2, buildStatus.buildRectY - buildStatus.buildingSelectImage->GetHeight() / 2);
		progressBar->Render
		(hdc, buildStatus.buildRectX - IMAGEMANAGER->FindImage("ZurgProgressBack")->GetWidth() / 2, buildStatus.buildRect.bottom);
	}

	buildStatus.buildImage->FrameRender(hdc, buildStatus.buildRect.left, buildStatus.buildRect.top, buildStatus.frameIndexX, buildStatus.frameIndexY);
}

void Hatchery::RenderUI(HDC hdc)
{
	if (isClick)
	{
		buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

		if (KEYMANAGER->IsToggleKey(VK_TAB))
		{
			for (int i = 0; i < COMMANDMAX; i++)
			{
				Rectangle(hdc, commandRect[i].left, commandRect[i].top, commandRect[i].right, commandRect[i].bottom);
			}
		}
		IMAGEMANAGER->FindImage("SelectLarva")->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
		IMAGEMANAGER->FindImage("SetRallyPoint")->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
		IMAGEMANAGER->FindImage("EvolveBurrow")->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
		IMAGEMANAGER->FindImage("LairRequires")->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
	}
}

