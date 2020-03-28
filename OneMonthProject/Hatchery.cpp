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

	buildStatus.buildImage = IMAGEMANAGER->FindImage("해처리");
	buildStatus.enemyBuildImage1 = IMAGEMANAGER->FindImage("EnemyHatchery");
	buildStatus.buildingSelectImage = IMAGEMANAGER->FindImage("4X3");
	buildStatus.buildingWireFrame = IMAGEMANAGER->FindImage("HatcheryWirefram");
	buildStatus.buildingFrontProgressImage = IMAGEMANAGER->FindImage("ZergProgressFront");
	buildStatus.buildingBackProgressImage = IMAGEMANAGER->FindImage("ZergProgressBack");

	buildStatus.buildRect = RectMake(buildXY.x, buildXY.y, 64 * 4, 64 * 3);
	buildStatus.buildCollisionRect = RectMake(buildXY.x, buildXY.y + 64, 64 * 4, 64 * 2);

	// 지어진 건물 위치 블록처리 for 문의 i 값은 가로 최대 수치 내부의 SetBlockTile은 세로를 설정해준다.
	for (int i = 0; i < 4; i++)
	{
		PLAYERMANAGER->SetBlockTile(buildXY.x + buildXY.y / TILEX + TILEX * i);
		PLAYERMANAGER->SetBlockTile(buildXY.x + buildXY.y / TILEX + TILEX * i + 1);
		PLAYERMANAGER->SetBlockTile(buildXY.x + buildXY.y / TILEX + TILEX * i + 2);
	}

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

	isTransLair = false;

	hatchery = true;
	lair = false;
	hive = false;

	progressBar->Init("images/UI/ZergProgressFront.bmp", "images/UI/ZergProgressBack.bmp", buildStatus.buildRect.left, buildStatus.buildRect.bottom, 107 * 2, 9 * 2);

	// 명령 슬롯 생성
	SetCommandSlot(SLOT1, new SelectLarva);
	SetCommandSlot(SLOT2, new SetRallyPoint);
	SetCommandSlot(SLOT3, new EvolveBurrow);
	SetCommandSlot(SLOT7, new LairRequires);

	// 명령 이미지 설정
	commandImage[SLOT1] = IMAGEMANAGER->FindImage("SelectLarva");
	commandImage[SLOT2] = IMAGEMANAGER->FindImage("SetRallyPoint");
	commandImage[SLOT3] = IMAGEMANAGER->FindImage("EvolveBurrow");
	commandImage[SLOT7] = IMAGEMANAGER->FindImage("LairRequires");
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
	// 해당 객체가 클릭 되었을 때
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		if (hatchery)
		{
			buildStatus.buidKind = HATCHERY;

			commandImage[SLOT7] = IMAGEMANAGER->FindImage("DisabledLairRequires");

			// 셀렉트 라바
			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					UNITMANAGER->SetSelectLarva(true);
					UNITMANAGER->SetXY(buildStatus.buildRectX, buildStatus.buildRectY);
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('S'))
			{
				UNITMANAGER->SetSelectLarva(true);
				UNITMANAGER->SetXY(buildStatus.buildRectX, buildStatus.buildRectY);
			}

			// 레어 변태
			if (BUILDMANAGER->GetHaveSpawningpool())
			{
				commandImage[SLOT7] = IMAGEMANAGER->FindImage("LairRequires");

				if (PtInRect(&commandRect[SLOT7], m_ptMouse))
				{
					if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
					{
						isTransLair = true;

						buildStatus.buildImage = IMAGEMANAGER->FindImage("transToLair");
					}
				}
				if (KEYMANAGER->IsOnceKeyDown('L'))
				{
					isTransLair = true;

					buildStatus.buildImage = IMAGEMANAGER->FindImage("transToLair");
				}
			}
		}
		else if (lair)
		{
			buildStatus.buidKind = LAIR;
			commandImage[SLOT7] = IMAGEMANAGER->FindImage("DisabledHiveRequires"); 

			// 셀렉트 라바
			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					UNITMANAGER->SetSelectLarva(true);
					UNITMANAGER->SetXY(buildStatus.buildRectX, buildStatus.buildRectY);
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('S'))
			{
				UNITMANAGER->SetSelectLarva(true);
				UNITMANAGER->SetXY(buildStatus.buildRectX, buildStatus.buildRectY);
			}

			// 하이브 변태
			if (BUILDMANAGER->GetHaveQueensnest())
			{
				commandImage[SLOT7] = IMAGEMANAGER->FindImage("HiveRequires"); 

				if (PtInRect(&commandRect[SLOT7], m_ptMouse))
				{
					if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
					{
						isTransHive = true;

						buildStatus.buildImage = IMAGEMANAGER->FindImage("transToHive");
					}
				}
				if (KEYMANAGER->IsOnceKeyDown('H'))
				{
					isTransHive = true;

					buildStatus.buildImage = IMAGEMANAGER->FindImage("transToHive");
				}
			}
		}
		else if (hive)
		{
			buildStatus.buidKind = HIVE;

		}
	}

	// 슬롯 위치 카메라 반영
	SetCommandRect();

	progressBar->SetGauge(buildStatus.buildingCurrentHp, buildStatus.buildingMaxHp);
	
	if (isTransLair || isTransHive)
	{
		// 여기 해야한다
		PlayTransformAnimation();
	}
	else
	{
		// 애니메이션 프레임 업데이트
		PlayAnimation();
	}
}

void Hatchery::Render(HDC hdc)
{	
	// 해당 객체가 클릭 되었을 때
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{  
		buildStatus.buildingSelectImage->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingSelectImageWidth, buildStatus.buildRectY - buildStatus.buildingSelectImageHeight + 15);
		progressBar->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingProgressWidth, buildStatus.buildRect.bottom + 10);
	}

	if (isTransLair)
	{
		buildStatus.buildImage->FrameRender(hdc, buildStatus.buildRect.left - 46, buildStatus.buildRect.top -72, buildStatus.frameIndexX, buildStatus.frameIndexY);
	}
	else if (isTransHive)
	{
		buildStatus.buildImage->FrameRender(hdc, buildStatus.buildRect.left - 54, buildStatus.buildRect.top - 108, buildStatus.frameIndexX, buildStatus.frameIndexY);
	}
	else
	{
		buildStatus.buildImage->FrameRender(hdc, buildStatus.buildRect.left - 64, buildStatus.buildRect.top - 64, buildStatus.frameIndexX, buildStatus.frameIndexY);
	}

	//if (buildStatus.playerNumber == PLAYER2 && buildStatus.buidKind == HATCHERY)
	//{
	//	buildStatus.enemyBuildImage1->FrameRender(hdc, buildStatus.buildRect.left, buildStatus.buildRect.top, buildStatus.frameIndexX, buildStatus.frameIndexY);
	//}
	
}

void Hatchery::RenderUI(HDC hdc)
{
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		if (hatchery)
		{
			buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

			if (KEYMANAGER->IsToggleKey(VK_TAB))
			{
				for (int i = 0; i < COMMANDMAX; i++)
				{
					Rectangle(hdc, commandRect[i].left, commandRect[i].top, commandRect[i].right, commandRect[i].bottom);
				}
			}
			commandImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
			commandImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
			commandImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
			commandImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
		}
		else if (lair)
		{
			buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

			commandImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
			commandImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
			commandImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
			commandImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
		}
		else if (hive)
		{

		}
	}
}

void Hatchery::PlayTransformAnimation()
{
	if (isTransLair)
	{
		buildStatus.frameIndexY = 0;

		buildStatus.frameCount++;
		buildStatus.buildImage->SetFrameY(buildStatus.frameIndexY);
		if (buildStatus.frameCount % 4 == 0)
		{
			buildStatus.frameCount = 0;
			if (buildStatus.frameIndexX >= buildStatus.buildImage->GetMaxFrameX())
			{
				buildStatus.frameIndexX = 0;
				isTransLair = false;

				hatchery = false;
				lair = true;
				hive = false;

				buildStatus.buildImage = IMAGEMANAGER->FindImage("레어");
			}
			buildStatus.buildImage->SetFrameX(buildStatus.frameIndexX);
			buildStatus.frameIndexX++;
		}
	}
	else if (isTransHive)
	{
		buildStatus.frameIndexY = 0;

		buildStatus.frameCount++;
		buildStatus.buildImage->SetFrameY(buildStatus.frameIndexY);
		if (buildStatus.frameCount % 5 == 0)
		{
			buildStatus.frameCount = 0;
			if (buildStatus.frameIndexX >= buildStatus.buildImage->GetMaxFrameX())
			{
				buildStatus.frameIndexX = 0;

				isTransHive = false;
				hatchery = false;
				lair = false;
				hive = true;

				buildStatus.buildImage = IMAGEMANAGER->FindImage("하이브");
			}
			buildStatus.buildImage->SetFrameX(buildStatus.frameIndexX);
			buildStatus.frameIndexX++;
		}

	}

}

