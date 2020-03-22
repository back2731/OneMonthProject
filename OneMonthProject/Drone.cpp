#include "stdafx.h"
#include "Drone.h"


Drone::Drone()
{
}


Drone::~Drone()
{
}

Drone::Drone(int _playerNumber, POINT birthXY)
{
	progressBar = new ProgressBar;
	unitStatus.unitKind = DRONE;

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 40;
	unitStatus.unitCurrentHp = 20;
	unitStatus.unitAtk = 5;
	unitStatus.unitDef = 0;
	unitStatus.unitTime = 0;

	unitStatus.unitMineralPrice = 50;
	unitStatus.unitGasPrice = 0;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("drone");
	unitStatus.unitShadowImage = IMAGEMANAGER->FindImage("droneShadow");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("2X2");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth() /3, unitStatus.unitImage->GetFrameHeight()/3);
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) / 2;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) / 2;

	unitStatus.frameCount = 0;
	unitStatus.frameIndexY = 5;
	direction = 5;
	isClick = false;
	testNum = 4;
	progressBar->Init("images/UI/ZurgUnitProgressFront.bmp", "images/UI/ZurgUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);

	InitAstar();
	
	// 명령 슬롯 생성
	SetCommandSlot(SLOT1, new MoveCommand);
	SetCommandSlot(SLOT2, new StopCommand);
	SetCommandSlot(SLOT3, new AttackCommand);
	SetCommandSlot(SLOT5, new Gathering);
	SetCommandSlot(SLOT7, new BaseBuilding);
	SetCommandSlot(SLOT8, new HighBuilding);
	SetCommandSlot(SLOT9, new Burrow);

	// 슬롯 위치 카메라 반영
	SetCommandRect();
}

HRESULT Drone::Init()
{
	return S_OK;
}

void Drone::Release()
{
}

void Drone::Update()
{
	progressBar->SetGauge(unitStatus.unitCurrentHp, unitStatus.unitMaxHp);

	if (isClick)
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			PLAYERMANAGER->SetInputCommandMove(true);
		}
		if (PLAYERMANAGER->GetInputCommandMove())
		{
			// 명령이 들어왔을 때 A*를 위한 값을 초기화해주고 실행bool변수를 true로 바꿔준다
			SetEndTile();
			SetAstarVector();
			SetStartTile();
		}
	}

	// A*실행
	UpdateAstar(unitStatus.unitRectX, unitStatus.unitRectY);
	
	// 변하는 각도에 따라 프레임을 바꿔준다.
	unitStatus.frameIndexY = ChangeImageFrame();
	
	// 길찾기를 통해 유닛을 이동한다.
	MoveUnit();

	// 애니메이션의 프레임을 돌린다.
	PlayAnimation();

	// 유닛 렉트를 재설정해준다.
	unitStatus.unitRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImage->GetFrameWidth() / 3, unitStatus.unitImage->GetFrameHeight() / 3);
}

void Drone::Render(HDC hdc)
{
	unitStatus.unitShadowImage->AlphaFrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImage->GetFrameWidth() / 2, 
		unitStatus.unitRectY - unitStatus.unitImage->GetFrameHeight() / 2, unitStatus.frameIndexX, unitStatus.frameIndexY, 125);
	if (isClick)
	{
		unitStatus.unitSelectImage->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitSelectImage->GetWidth() / 2, unitStatus.unitRectY - unitStatus.unitSelectImage->GetHeight() / 2);
		progressBar->Render
		(hdc, unitStatus.unitRectX - IMAGEMANAGER->FindImage("ZurgUnitProgressBack")->GetWidth() / 2, unitStatus.unitRectY + 40);
	}
	unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImage->GetFrameWidth() / 2, 
		unitStatus.unitRectY - unitStatus.unitImage->GetFrameHeight() / 2, unitStatus.frameIndexX, unitStatus.frameIndexY);
	for (int i = 0; i < TILESIZE; i++)
	{
		if (KEYMANAGER->IsToggleKey(VK_TAB))
		{
			if (_tileMap[i].block == true)
			{
				Rectangle(hdc, _tileMap[i].rect.left, _tileMap[i].rect.top, _tileMap[i].rect.right, _tileMap[i].rect.bottom);
				HBRUSH brush = CreateSolidBrush(RGB(0, 102, 0));
				FillRect(hdc, &_tileMap[i].rect, brush);
				DeleteObject(brush);

			}
		}
	}
}

void Drone::RenderUI(HDC hdc)
{	
	// 슬롯 위치 카메라 반영
	SetCommandRect();
	if (isClick)
	{
		//buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

		if (KEYMANAGER->IsToggleKey(VK_TAB))
		{
			for (int i = 0; i < COMMANDMAX; i++)
			{
				Rectangle(hdc, commandRect[i].left, commandRect[i].top, commandRect[i].right, commandRect[i].bottom);
			}
		}

		IMAGEMANAGER->FindImage("Move")->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
		IMAGEMANAGER->FindImage("Stop")->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
		IMAGEMANAGER->FindImage("Attack")->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
		IMAGEMANAGER->FindImage("Gathering")->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
		IMAGEMANAGER->FindImage("BaseBuilding")->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
		IMAGEMANAGER->FindImage("HighBuilding")->Render(hdc, commandRect[SLOT8].left, commandRect[SLOT8].top);
		IMAGEMANAGER->FindImage("EvolveBurrow")->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);
	}

}

void Drone::PlayAnimation()
{
	unitStatus.frameCount++;
	unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
	if (unitStatus.frameCount % 10 == 0)
	{
		unitStatus.frameCount = 0;
		if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX() - 5)
		{
			unitStatus.frameIndexX = 0;
		}
		unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
		unitStatus.frameIndexX++;
	}
}
