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

	larvaVector.push_back(UNITMANAGER->CreateLarva({ buildStatus.buildRect.left + (buildStatus.buildRect.right - buildStatus.buildRect.left) / 2 + 50, buildStatus.buildRect.bottom - 40 }));
	larvaVector.push_back(UNITMANAGER->CreateLarva({ buildStatus.buildRect.left + (buildStatus.buildRect.right - buildStatus.buildRect.left) / 2, buildStatus.buildRect.bottom - 40 }));
	larvaVector.push_back(UNITMANAGER->CreateLarva({ buildStatus.buildRect.left + (buildStatus.buildRect.right - buildStatus.buildRect.left) / 2 - 50, buildStatus.buildRect.bottom - 40 }));

	PROGRESSMANAGER->Init("images/UI/ZurgProgressFront.bmp", "images/UI/ZurgProgressBack.bmp", buildStatus.buildRect.left, buildStatus.buildRect.bottom, 107 * 2, 9 * 2);

	// 명령 슬롯 생성 - > 함수화
	commandSlot[0] = new SelectLarva;
	commandSlot[1] = new SetRallyPoint;
	commandSlot[2] = new EvolveBurrow;
	commandSlot[6] = new LairRequires;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			commandRect[i * 3 + j] = RectMake(937 + (j * 85), 677 + (i * 75), 70, 70);
		}
	}
}

HRESULT Hatchery::Init()
{
	return S_OK;
}

void Hatchery::Release()
{

}

void Hatchery::Update()
{
	// 해처리 애니메이션 프레임 업데이트
	PlayAnimation();

	for (int i = 0; i < larvaVector.size(); i++)
	{
		larvaVector[i]->Update();
	}

	// 해당 객체가 클릭 되었을 때
	if (isClick)
	{
		// 명령 컨트롤 업데이트
		if (PtInRect(&commandRect[0], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				commandSlot[0]->Update();
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			commandRect[i * 3 + j] = RectMake(CAMERAMANAGER->GetCameraCenter().x + 335 + (j * 85), CAMERAMANAGER->GetCameraCenter().y + 225 + (i * 75), 70, 70);

		}
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
	{
		buildStatus.buildingCurrentHp -= 50;
	}
	PROGRESSMANAGER->SetGauge(buildStatus.buildingCurrentHp, buildStatus.buildingMaxHp);
}

void Hatchery::Render(HDC hdc)
{	
	// 해당 객체가 클릭 되었을 때
	if (isClick)
	{  
		buildStatus.buildingSelectImage->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingSelectImage->GetWidth() / 2, buildStatus.buildRectY - buildStatus.buildingSelectImage->GetHeight() / 2);
		PROGRESSMANAGER->Render
		(hdc, buildStatus.buildRectX - IMAGEMANAGER->FindImage("ZurgProgressBack")->GetWidth() / 2, buildStatus.buildRect.bottom - 75);
	}

	buildStatus.buildImage->FrameRender(hdc, buildStatus.buildRect.left, buildStatus.buildRect.top, buildStatus.frameIndexX, buildStatus.frameIndexY);

	for (int i = 0; i < larvaVector.size(); i++)
	{
		larvaVector[i]->Render(hdc);
	}		

	if (isClick)
	{
		buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260 , CAMERAMANAGER->GetCameraCenter().y + 280);

		if (KEYMANAGER->IsToggleKey(VK_TAB))
		{
			for (int i = 0; i < COMMANDMAX; i++)
			{
				Rectangle(hdc, commandRect[i].left, commandRect[i].top, commandRect[i].right, commandRect[i].bottom);
			}
		}
		IMAGEMANAGER->FindImage("SelectLarva")->Render(hdc, commandRect[0].left, commandRect[0].top);
		IMAGEMANAGER->FindImage("SetRallyPoint")->Render(hdc, commandRect[1].left, commandRect[1].top);
		IMAGEMANAGER->FindImage("EvolveBurrow")->Render(hdc, commandRect[2].left, commandRect[2].top);
		IMAGEMANAGER->FindImage("LairRequires")->Render(hdc, commandRect[6].left, commandRect[6].top);
	}	
}

void Hatchery::PlayAnimation()
{
	buildStatus.frameIndexY = 0;

	buildStatus.frameCount++;
	buildStatus.buildImage->SetFrameY(buildStatus.frameIndexY);
	if (buildStatus.frameCount % 10 == 0)
	{
		buildStatus.frameCount = 0;
		if (buildStatus.frameIndexX >= buildStatus.buildImage->GetMaxFrameX())
		{
			buildStatus.frameIndexX = 0;
		}
		buildStatus.buildImage->SetFrameX(buildStatus.frameIndexX);
		buildStatus.frameIndexX++;
	}
}
