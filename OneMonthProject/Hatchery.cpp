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
	buildStatus.enemyBuildImage1 = IMAGEMANAGER->FindImage("EnemyHatchery");
	buildStatus.buildingSelectImage = IMAGEMANAGER->FindImage("4X3");
	buildStatus.buildingWireFrame = IMAGEMANAGER->FindImage("HatcheryWirefram");
	buildStatus.buildingFrontProgressImage = IMAGEMANAGER->FindImage("ZergProgressFront");
	buildStatus.buildingBackProgressImage = IMAGEMANAGER->FindImage("ZergProgressBack");

	buildStatus.buildRect = RectMake(buildXY.x, buildXY.y, buildStatus.buildImage->GetFrameWidth(), buildStatus.buildImage->GetFrameHeight());
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

	// ��� ���� ����
	SetCommandSlot(SLOT1, new SelectLarva);
	SetCommandSlot(SLOT2, new SetRallyPoint);
	SetCommandSlot(SLOT3, new EvolveBurrow);
	SetCommandSlot(SLOT7, new LairRequires);

	// ��� �̹��� ����
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

	// �ִϸ��̼� ������ ������Ʈ
	PlayAnimation();

	// �ش� ��ü�� Ŭ�� �Ǿ��� ��
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		// ����Ʈ ���
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
	}

	// ���� ��ġ ī�޶� �ݿ�
	SetCommandRect();

	progressBar->SetGauge(buildStatus.buildingCurrentHp, buildStatus.buildingMaxHp);
}

void Hatchery::Render(HDC hdc)
{	
	// �ش� ��ü�� Ŭ�� �Ǿ��� ��
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{  
		buildStatus.buildingSelectImage->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingSelectImageWidth, buildStatus.buildRectY - buildStatus.buildingSelectImageHeight + 15);
		progressBar->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingProgressWidth, buildStatus.buildRect.bottom + 10);
	}

	if (buildStatus.playerNumber == PLAYER1)
	{
		buildStatus.buildImage->FrameRender(hdc, buildStatus.buildRect.left, buildStatus.buildRect.top, buildStatus.frameIndexX, buildStatus.frameIndexY);
	}
	else if (buildStatus.playerNumber == PLAYER2)
	{
		buildStatus.enemyBuildImage1->FrameRender(hdc, buildStatus.buildRect.left, buildStatus.buildRect.top, buildStatus.frameIndexX, buildStatus.frameIndexY);
	}
}

void Hatchery::RenderUI(HDC hdc)
{
	if (isClick && buildStatus.playerNumber == PLAYER1)
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
		commandImage[SLOT3]-> Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
		commandImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
	}
}

