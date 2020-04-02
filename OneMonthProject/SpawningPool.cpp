#include "stdafx.h"
#include "SpawningPool.h"


SpawningPool::SpawningPool()
{
}


SpawningPool::~SpawningPool()
{
}

SpawningPool::SpawningPool(int _playerNumber, POINT buildXY)
{
	progressBar = new ProgressBar;

	buildStatus.buidKind = SPAWNINGPOOL;

	buildStatus.playerNumber = _playerNumber;

	buildStatus.buildingMaxHp = 750;
	buildStatus.buildingCurrentHp = 725;
	buildStatus.buildingAtk = 0;
	buildStatus.buildingDef = 1;
	buildStatus.buildTime = 80;

	buildStatus.buildingMineralPrice = 200;
	buildStatus.buildingGasPrice = 0;

	buildStatus.buildImage = IMAGEMANAGER->FindImage("SpawningPool");
	//buildStatus.enemyBuildImage1 = IMAGEMANAGER->FindImage("EnemyHatchery");
	buildStatus.buildingSelectImage = IMAGEMANAGER->FindImage("3X2");
	buildStatus.buildingWireFrame = IMAGEMANAGER->FindImage("SpawningPoolWirefram");
	buildStatus.buildingFrontProgressImage = IMAGEMANAGER->FindImage("ZergProgressFront");
	buildStatus.buildingBackProgressImage = IMAGEMANAGER->FindImage("ZergProgressBack");

	buildStatus.buildRect = RectMake(buildXY.x, buildXY.y, 64 * 3, 64 * 2);
	buildStatus.buildCollisionRect = RectMake(buildXY.x, buildXY.y + 64, 64 * 3, 64);

	// ������ �ǹ� ��ġ ���ó�� for ���� i ���� ���� �ִ� ��ġ ������ SetBlockTile�� ���θ� �������ش�.
	for (int i = 0; i < 3; i++)
	{
		PLAYERMANAGER->SetBlockTile(buildXY.x + buildXY.y / TILEX + TILEX * i);
		PLAYERMANAGER->SetBlockTile(buildXY.x + buildXY.y / TILEX + TILEX * i + 1);
	}

	buildStatus.buildRectX = buildStatus.buildRect.left + (buildStatus.buildRect.right - buildStatus.buildRect.left) / 2;
	buildStatus.buildRectY = buildStatus.buildRect.top + (buildStatus.buildRect.bottom - buildStatus.buildRect.top) / 2;

	buildStatus.buildingImageWidthHalf = buildStatus.buildImage->GetWidth() / 2;
	buildStatus.buildingImageHeightHalf = buildStatus.buildImage->GetHeight() / 2;

	buildStatus.buildingSelectImageWidth = buildStatus.buildingSelectImage->GetWidth() / 2;
	buildStatus.buildingSelectImageHeight = buildStatus.buildingSelectImage->GetHeight() / 2;

	buildStatus.buildingProgressWidth = buildStatus.buildingBackProgressImage->GetWidth() / 2;
	buildStatus.buildingProgressHeight = buildStatus.buildingBackProgressImage->GetHeight() / 2;
	
	buildStatus.buildingPortraitsImage = IMAGEMANAGER->FindImage("portraitsOverMind");
	buildStatus.buildingPortraitsCount = 0;
	buildStatus.buildingPortraitsFrameY = 0;

	buildStatus.frameCount = 0;
	buildStatus.frameIndexX = 0;
	buildStatus.frameIndexY = 0;
	isClick = false;

	progressBar->Init("images/UI/ZergProgressFront.bmp", "images/UI/ZergProgressBack.bmp", buildStatus.buildRect.left, buildStatus.buildRect.bottom, 107 * 2, 9 * 2);

	//// ��� ���� ����
	//SetCommandSlot(SLOT1, new SelectLarva);
	//SetCommandSlot(SLOT2, new SetRallyPoint);
	//SetCommandSlot(SLOT3, new EvolveBurrow);
	//SetCommandSlot(SLOT7, new LairRequires);

	//// ��� �̹��� ����
	//commandImage[SLOT1] = IMAGEMANAGER->FindImage("SelectLarva");
	//commandImage[SLOT2] = IMAGEMANAGER->FindImage("SetRallyPoint");
	//commandImage[SLOT3] = IMAGEMANAGER->FindImage("EvolveBurrow");
	//commandImage[SLOT7] = IMAGEMANAGER->FindImage("LairRequires");

	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() - 1);
}

HRESULT SpawningPool::Init()
{
	return S_OK;
}

void SpawningPool::Release()
{
	SAFE_DELETE(progressBar);
}

void SpawningPool::Update()
{	
	// �ִϸ��̼� ������ ������Ʈ
	PlayAnimation();
	PlayPortraits();

	// �ش� ��ü�� Ŭ�� �Ǿ��� ��
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		// 
		if (PtInRect(&commandRect[SLOT1], m_ptMouse))
		{
		}
	}

	// ���� ��ġ ī�޶� �ݿ�
	SetCommandRect();

	progressBar->SetGauge(buildStatus.buildingCurrentHp, buildStatus.buildingMaxHp);
}

void SpawningPool::Render(HDC hdc)
{	
	// �ش� ��ü�� Ŭ�� �Ǿ��� ��
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		buildStatus.buildingSelectImage->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingSelectImageWidth, buildStatus.buildRectY - buildStatus.buildingSelectImageHeight);
		progressBar->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingProgressWidth, buildStatus.buildRect.bottom);
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

void SpawningPool::RenderUI(HDC hdc)
{
	buildStatus.buildingPortraitsImage->FrameRender(hdc, CAMERAMANAGER->GetCameraCenter().x + 170, CAMERAMANAGER->GetCameraCenter().y + 310, buildStatus.buildingPortraitsFrameX, buildStatus.buildingPortraitsFrameY);

	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

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

		SetTextColor(hdc, RGB(0, 222, 0));
		sprintf_s(str, "%d", buildStatus.buildingCurrentHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 250, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		sprintf_s(str, "/  %d", buildStatus.buildingMaxHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 200, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));

		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(str, "Zerg SpawningPool");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 80, CAMERAMANAGER->GetCameraCenter().y + 290, str, strlen(str));
	}
}
