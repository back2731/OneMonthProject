#include "stdafx.h"
#include "HydraliskDen.h"


HydraliskDen::HydraliskDen()
{
}


HydraliskDen::~HydraliskDen()
{
}

HydraliskDen::HydraliskDen(int _playerNumber, POINT buildXY)
{
	progressBar = new ProgressBar;

	buildStatus.buidKind = HYDRALISKDEN;

	buildStatus.playerNumber = _playerNumber;

	buildStatus.buildingMaxHp = 850;
	buildStatus.buildingCurrentHp = 725;
	buildStatus.buildingAtk = 0;
	buildStatus.buildingDef = 1;
	buildStatus.buildTime = 40;

	buildStatus.buildingMineralPrice = 100;
	buildStatus.buildingGasPrice = 50;

	buildStatus.buildImage = IMAGEMANAGER->FindImage("HydraliskDen");
	//buildStatus.enemyBuildImage1 = IMAGEMANAGER->FindImage("EnemyHatchery");
	buildStatus.buildingSelectImage = IMAGEMANAGER->FindImage("3X2");
	//buildStatus.buildingWireFrame = IMAGEMANAGER->FindImage("SpawningPoolWirefram");
	buildStatus.buildingFrontProgressImage = IMAGEMANAGER->FindImage("ZergProgressFront");
	buildStatus.buildingBackProgressImage = IMAGEMANAGER->FindImage("ZergProgressBack");

	buildStatus.buildRect = RectMake(buildXY.x, buildXY.y, 96*2, 64*2);
	buildStatus.buildRectX = buildStatus.buildRect.left + (buildStatus.buildRect.right - buildStatus.buildRect.left) / 2;
	buildStatus.buildRectY = buildStatus.buildRect.top + (buildStatus.buildRect.bottom - buildStatus.buildRect.top) / 2;

	buildStatus.buildingImageWidthHalf = buildStatus.buildImage->GetWidth() / 2;
	buildStatus.buildingImageHeightHalf = buildStatus.buildImage->GetHeight() / 2;

	buildStatus.buildingSelectImageWidth = buildStatus.buildingSelectImage->GetWidth() / 2;
	buildStatus.buildingSelectImageHeight = buildStatus.buildingSelectImage->GetHeight() / 2;

	buildStatus.buildingProgressWidth = buildStatus.buildingBackProgressImage->GetWidth() / 2;
	buildStatus.buildingProgressHeight = buildStatus.buildingBackProgressImage->GetHeight() / 2;

	buildStatus.frameCount = 0;
	buildStatus.frameIndexX = 0;
	buildStatus.frameIndexY = 0;
	isClick = false;

	progressBar->Init("images/UI/ZergProgressFront.bmp", "images/UI/ZergProgressBack.bmp", buildStatus.buildRect.left, buildStatus.buildRect.bottom, 107 * 2, 9 * 2);

	//// 명령 슬롯 생성
	//SetCommandSlot(SLOT1, new SelectLarva);
	//SetCommandSlot(SLOT2, new SetRallyPoint);
	//SetCommandSlot(SLOT3, new EvolveBurrow);
	//SetCommandSlot(SLOT7, new LairRequires);

	//// 명령 이미지 설정
	//commandImage[SLOT1] = IMAGEMANAGER->FindImage("SelectLarva");
	//commandImage[SLOT2] = IMAGEMANAGER->FindImage("SetRallyPoint");
	//commandImage[SLOT3] = IMAGEMANAGER->FindImage("EvolveBurrow");
	//commandImage[SLOT7] = IMAGEMANAGER->FindImage("LairRequires");
}

HRESULT HydraliskDen::Init()
{
	return S_OK;
}

void HydraliskDen::Release()
{
	SAFE_DELETE(progressBar);
}

void HydraliskDen::Update()
{	
	// 애니메이션 프레임 업데이트
	PlayAnimation();

	// 해당 객체가 클릭 되었을 때
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		// 
		if (PtInRect(&commandRect[SLOT1], m_ptMouse))
		{
		}
	}

	// 슬롯 위치 카메라 반영
	SetCommandRect();

	progressBar->SetGauge(buildStatus.buildingCurrentHp, buildStatus.buildingMaxHp);
}

void HydraliskDen::Render(HDC hdc)
{		
	//해당 객체가 클릭 되었을 때
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		buildStatus.buildingSelectImage->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingSelectImageWidth, buildStatus.buildRectY - buildStatus.buildingSelectImageHeight);
		progressBar->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingProgressWidth, buildStatus.buildRect.bottom);
	}

	if (buildStatus.playerNumber == PLAYER1)
	{
		buildStatus.buildImage->FrameRender(hdc, buildStatus.buildRect.left, buildStatus.buildRect.top - 40, buildStatus.frameIndexX, buildStatus.frameIndexY);
	}
	else if (buildStatus.playerNumber == PLAYER2)
	{
		buildStatus.enemyBuildImage1->FrameRender(hdc, buildStatus.buildRect.left, buildStatus.buildRect.top - 40, buildStatus.frameIndexX, buildStatus.frameIndexY);
	}
}

void HydraliskDen::RenderUI(HDC hdc)
{
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		//buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

		//if (KEYMANAGER->IsToggleKey(VK_TAB))
		//{
		//	for (int i = 0; i < COMMANDMAX; i++)
		//	{
		//		Rectangle(hdc, commandRect[i].left, commandRect[i].top, commandRect[i].right, commandRect[i].bottom);
		//	}
		//}
		//commandImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
		//commandImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
		//commandImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
		//commandImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
	}
}
