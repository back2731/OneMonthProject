#include "stdafx.h"
#include "Hydralisk.h"


Hydralisk::Hydralisk()
{
}


Hydralisk::~Hydralisk()
{
}

Hydralisk::Hydralisk(int _playerNumber, POINT birthXY)
{
	progressBar = new ProgressBar;
	unitStatus.unitKind = HYDRALISK;

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 35;
	unitStatus.unitCurrentHp = 35;
	unitStatus.unitAtk = 5;
	unitStatus.unitDef = 0;
	unitStatus.unitTime = 0;
	unitStatus.unitSpeed = 4;

	unitStatus.unitMineralPrice = 50;
	unitStatus.unitGasPrice = 0;

	unitStatus.unitState = IDLE;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("hydra");
	unitStatus.unitWireFrame = IMAGEMANAGER->FindImage("hydraWirefram");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("2X2");
	unitStatus.unitFrontProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressFront");
	unitStatus.unitBackProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressBack");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth() * 0.25, unitStatus.unitImage->GetFrameHeight() * 0.25);
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) * 0.5;;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) * 0.5;;
	unitStatus.unitSearchingRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImage->GetFrameWidth() * 2, unitStatus.unitImage->GetFrameHeight() * 2);

	unitStatus.unitImageWidthHalf = unitStatus.unitImage->GetFrameWidth() * 0.5;
	unitStatus.unitImageHeightHalf = unitStatus.unitImage->GetFrameHeight() * 0.5;
	unitStatus.unitImageWidthQuarter = unitStatus.unitImage->GetFrameWidth() * 0.25;
	unitStatus.unitImageHeightQuarter = unitStatus.unitImage->GetFrameHeight() * 0.25;

	unitStatus.unitSelectImageWidth = unitStatus.unitSelectImage->GetWidth() * 0.5;
	unitStatus.unitSelectImageHeight = unitStatus.unitSelectImage->GetHeight() * 0.5;

	unitStatus.unitProgressWidth = unitStatus.unitBackProgressImage->GetWidth() * 0.5;
	unitStatus.unitProgressHeight = unitStatus.unitBackProgressImage->GetHeight() * 0.5;

	unitStatus.frameCount = 0;
	unitStatus.frameIndexX = 5;
	unitStatus.frameIndexY = 5;

	isClick = false;
	progressBar->Init("images/UI/ZergUnitProgressFront.bmp", "images/UI/ZergUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);

	InitAstar();
	SetBlock();

	// 명령 슬롯 생성
	SetCommandSlot(SLOT1, new MoveCommand);
	SetCommandSlot(SLOT2, new StopCommand);
	SetCommandSlot(SLOT3, new AttackCommand);
	SetCommandSlot(SLOT4, new PatrolCommand);
	SetCommandSlot(SLOT5, new HoldCommand);
	SetCommandSlot(SLOT9, new Burrow);

	// 명령 이미지 설정
	commandImage[SLOT1] = IMAGEMANAGER->FindImage("Move");
	commandImage[SLOT2] = IMAGEMANAGER->FindImage("Stop");
	commandImage[SLOT3] = IMAGEMANAGER->FindImage("Attack");
	commandImage[SLOT4] = IMAGEMANAGER->FindImage("Patrol");
	commandImage[SLOT5] = IMAGEMANAGER->FindImage("Hold");
	commandImage[SLOT9] = IMAGEMANAGER->FindImage("EvolveBurrow");

	// 슬롯 위치 카메라 반영
	SetCommandRect();
}

HRESULT Hydralisk::Init()
{
	return E_NOTIMPL;
}

void Hydralisk::Release()
{
}

void Hydralisk::Update()
{
	progressBar->SetGauge(unitStatus.unitCurrentHp, unitStatus.unitMaxHp);

	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			PLAYERMANAGER->SetInputCommandMove(true);
			// 설치하는 해당 위치를 저장해준다.
			for (int i = 0; i < TILESIZE; i++)
			{
				if (PtInRect(&_tileMap[i].rect, m_ptMouse))
				{
					PLAYERMANAGER->SetSaveUnitPosition(i);
					saveUnitPosition = i;
				}
			}
			isSearch = PLAYERMANAGER->GetIsSearch();
		}

		if (PLAYERMANAGER->GetInputCommandMove())
		{
			// 명령이 들어왔을 때 A*를 위한 값을 초기화해주고 실행bool변수를 true로 바꿔준다
			SetEndTile();
			SetAstarVector();
			SetStartTile();
			PLAYERMANAGER->SetChangeState(MOVE);
			unitStatus.unitState = PLAYERMANAGER->GetChangeState();
		}
	}
	else
	{

	}

	// 애니메이션의 프레임을 돌린다.
	PlayAnimation();

	if (isSearch)
	{
		PLAYERMANAGER->SetChangeState(IDLE);
		unitStatus.unitState = PLAYERMANAGER->GetChangeState();
	}
	else if (IntersectRect(&tempRect, &_tileMap[PLAYERMANAGER->GetSaveUnitPosition()].rect, &unitStatus.unitRect))
	{
		PLAYERMANAGER->SetChangeState(IDLE);
		unitStatus.unitState = PLAYERMANAGER->GetChangeState();
	}

	// A*실행
	UpdateAstar(unitStatus.unitRectX, unitStatus.unitRectY);

	// 변하는 각도에 따라 프레임을 바꿔준다.
	unitStatus.frameIndexY = ChangeImageFrame();

	// 길찾기를 통해 유닛을 이동한다.
	MoveUnit(unitStatus.unitSpeed);

	// 유닛 렉트를 재설정해준다.
	unitStatus.unitRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImageWidthQuarter, unitStatus.unitImageHeightQuarter);
	unitStatus.unitSearchingRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImage->GetFrameWidth() * 2, unitStatus.unitImage->GetFrameHeight() * 2);
}

void Hydralisk::Render(HDC hdc)
{
	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		Rectangle(hdc, unitStatus.unitSearchingRect.left, unitStatus.unitSearchingRect.top, unitStatus.unitSearchingRect.right, unitStatus.unitSearchingRect.bottom);
	}

	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		unitStatus.unitSelectImage->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitSelectImageWidth, unitStatus.unitRectY - unitStatus.unitSelectImageHeight);
		progressBar->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitProgressWidth, unitStatus.unitRectY + 20);
	}

	unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImageWidthHalf,
		unitStatus.unitRectY - unitStatus.unitImageHeightHalf, unitStatus.frameIndexX, unitStatus.frameIndexY);
}

void Hydralisk::RenderUI(HDC hdc)
{	
	// 슬롯 위치 카메라 반영
	SetCommandRect();
	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		unitStatus.unitWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

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
		commandImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top);
		commandImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
		commandImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);

		SetTextColor(hdc, RGB(0, 222, 0));
		sprintf_s(str, "%d", unitStatus.unitCurrentHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 240, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		sprintf_s(str, "/   %d", unitStatus.unitMaxHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 200, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));

		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(str, "Zerg Hydralisk");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 80, CAMERAMANAGER->GetCameraCenter().y + 290, str, strlen(str));
	}
}

void Hydralisk::PlayAnimation()
{
	if (unitStatus.unitState == IDLE)
	{
		unitStatus.frameIndexX = 5;
		unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
	}
	else if (unitStatus.unitState == MOVE)
	{
		unitStatus.frameCount++;
		if (unitStatus.frameCount % 5 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 5;
			}
			unitStatus.frameIndexX++;
		}
	}
	else if (unitStatus.unitState == ATTACK)
	{
		unitStatus.frameCount++;
		if (unitStatus.frameCount % 7 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX() - 7)
			{
				unitStatus.frameIndexX = 0;
			}
			unitStatus.frameIndexX++;
		}
	}

}
