#include "stdafx.h"
#include "Overlord.h"


Overlord::Overlord()
{
}


Overlord::~Overlord()
{
}

Overlord::Overlord(int _playerNumber, POINT birthXY)
{
	progressBar = new ProgressBar;
	unitStatus.unitKind = OVERLORD;

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 200;
	unitStatus.unitCurrentHp = 200;
	unitStatus.unitAtk = 0;
	unitStatus.unitDef = 0;
	unitStatus.unitBaseAtk = 0;
	unitStatus.unitBaseDef = 0;
	unitStatus.unitTime = 0;
	unitStatus.unitSpeed = 2;

	unitStatus.unitMineralPrice = 50;
	unitStatus.unitGasPrice = 0;

	unitStatus.unitState = IDLE;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("overlord");
	unitStatus.unitWireFrame = IMAGEMANAGER->FindImage("overlordWirefram");
	unitStatus.unitShadowImage = IMAGEMANAGER->FindImage("overlordShadow");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("2X2");
	unitStatus.unitFrontProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressFront");
	unitStatus.unitBackProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressBack");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth(), unitStatus.unitImage->GetFrameHeight());
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) * 0.5;;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) * 0.5;;

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
	unitStatus.frameIndexY = 3;

	unitStatus.unitPortraitsImage = IMAGEMANAGER->FindImage("portraitsOverlord");
	unitStatus.unitPortraitsCount = 0;
	unitStatus.unitPortraitsFrameY = 0;

	isClick = false;
	progressBar->Init("images/UI/ZergUnitProgressFront.bmp", "images/UI/ZergUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);

	InitAstar();
	//SetBlock();

	// 명령 슬롯 생성
	SetCommandSlot(SLOT1, new MoveCommand);
	SetCommandSlot(SLOT2, new StopCommand);
	SetCommandSlot(SLOT4, new PatrolCommand);
	SetCommandSlot(SLOT5, new HoldCommand);

	// 명령 이미지 설정
	commandImage[SLOT1] = IMAGEMANAGER->FindImage("Move");
	commandImage[SLOT2] = IMAGEMANAGER->FindImage("Stop");
	commandImage[SLOT4] = IMAGEMANAGER->FindImage("Patrol");
	commandImage[SLOT5] = IMAGEMANAGER->FindImage("Hold");
	
	abilityImage[SLOT1] = IMAGEMANAGER->FindImage("flyerCarapace");

	// 슬롯 위치 카메라 반영
	SetCommandRect();
	SetAbilityRect();

	PLAYERMANAGER->SetmaxPopulation(PLAYERMANAGER->GetmaxPopulation() + 8);

}

HRESULT Overlord::Init()
{
	return S_OK;
}

void Overlord::Release()
{
}

void Overlord::Update()
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

	if (IntersectRect(&tempRect, &_tileMap[PLAYERMANAGER->GetSaveUnitPosition()].rect, &unitStatus.unitRect))
	{
		PLAYERMANAGER->SetChangeState(IDLE);
		unitStatus.unitState = PLAYERMANAGER->GetChangeState();
	}


	// 애니메이션의 프레임을 돌린다.
	PlayAnimation();
	PlayPortraits();

	if (isSearch)
	{

	}

	// A*실행
	UpdateAstar(unitStatus.unitRectX, unitStatus.unitRectY);

	// 변하는 각도에 따라 프레임을 바꿔준다.
	unitStatus.frameIndexY = ChangeImageFrame();

	// 길찾기를 통해 유닛을 이동한다.
	MoveUnit(unitStatus.unitSpeed);

	// 유닛 렉트를 재설정해준다.
	unitStatus.unitRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImageWidthHalf, unitStatus.unitImageHeightHalf);

	// 스파이어에서 업그레이드를 해야한다
	//unitStatus.unitDef = 0 + UPGRADEMANAGER->GetEvolveCarapace();
	unitStatus.unitPositionRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, 2, 2);

}

void Overlord::Render(HDC hdc)
{
	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		unitStatus.unitSelectImage->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitSelectImageWidth, unitStatus.unitRectY - unitStatus.unitSelectImageHeight);
		progressBar->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitProgressWidth, unitStatus.unitRectY + 20);
	}

	unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImageWidthHalf,
		unitStatus.unitRectY - unitStatus.unitImageHeightHalf, unitStatus.frameIndexX, unitStatus.frameIndexY);
	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		Rectangle(hdc, unitStatus.unitRect.left, unitStatus.unitRect.top, unitStatus.unitRect.right, unitStatus.unitRect.bottom);
	}
}

void Overlord::RenderUI(HDC hdc)
{
	// 슬롯 위치 카메라 반영
	SetCommandRect();
	SetAbilityRect();

	unitStatus.unitPortraitsImage->FrameRender(hdc, CAMERAMANAGER->GetCameraCenter().x + 170, CAMERAMANAGER->GetCameraCenter().y + 310, unitStatus.unitPortraitsFrameX, unitStatus.unitPortraitsFrameY);

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
		commandImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top);
		commandImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
		
		// 명령 슬롯 설명 렌더
		if (PtInRect(&commandRect[SLOT1], m_ptMouse))
		{
			descriptionImage[SLOT1] = IMAGEMANAGER->FindImage("MoveUI");
			descriptionImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].bottom);
		}
		if (PtInRect(&commandRect[SLOT2], m_ptMouse))
		{
			descriptionImage[SLOT2] = IMAGEMANAGER->FindImage("StopUI");
			descriptionImage[SLOT2]->Render(hdc, commandRect[SLOT2].left - descriptionImage[SLOT2]->GetWidth() / 2, commandRect[SLOT2].bottom);
		}
		if (PtInRect(&commandRect[SLOT4], m_ptMouse))
		{
			descriptionImage[SLOT4] = IMAGEMANAGER->FindImage("PatrolUI");
			descriptionImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top - descriptionImage[SLOT4]->GetHeight());
		}
		if (PtInRect(&commandRect[SLOT5], m_ptMouse))
		{
			descriptionImage[SLOT5] = IMAGEMANAGER->FindImage("holdPositionUI");
			descriptionImage[SLOT5]->Render(hdc, commandRect[SLOT5].left - descriptionImage[SLOT5]->GetWidth() / 2, commandRect[SLOT5].top - descriptionImage[SLOT5]->GetHeight());
		}

		// 능력치 이미지 렌더
		abilityImage[SLOT1]->Render(hdc, abilityRect[SLOT1].left, abilityRect[SLOT1].top);

		SetTextColor(hdc, RGB(0, 222, 0));
		sprintf_s(str, "%d", unitStatus.unitCurrentHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 240, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		sprintf_s(str, "/   %d", unitStatus.unitMaxHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 200, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));

		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(str, "Zerg Overlord");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 80, CAMERAMANAGER->GetCameraCenter().y + 290, str, strlen(str));

		// 능력치 업그레이드 단계 렌더 ( 스파이어에서 업그레이드 진행 필요)
		sprintf_s(str, "0", UPGRADEMANAGER->GetEvolveCarapace());
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 60, CAMERAMANAGER->GetCameraCenter().y + 419, str, strlen(str));

		// 업그레이드 반영 렌더
		HFONT myFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "돋움체");
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);

		if (PtInRect(&abilityRect[SLOT1], m_ptMouse))
		{
			abilityDescriptionImage[SLOT1] = IMAGEMANAGER->FindImage("zergFlyerCarapaceUI");
			abilityDescriptionImage[SLOT1]->Render(hdc, abilityRect[SLOT1].right, abilityRect[SLOT1].top);

			sprintf_s(str, "0 + 0", unitStatus.unitBaseDef, UPGRADEMANAGER->GetEvolveCarapace());
			TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x + 42, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		}

		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}
}

void Overlord::RenderShadow(HDC hdc)
{
	unitStatus.unitShadowImage->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImageWidthHalf,
		unitStatus.unitRectY - unitStatus.unitImageHeightHalf + 80, unitStatus.frameIndexX, unitStatus.frameIndexY);
}

void Overlord::PlayAnimation()
{
	if (unitStatus.unitState == IDLE)
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
	else if (unitStatus.unitState == MOVE)
	{
		unitStatus.frameCount++;
		if (unitStatus.frameCount % 3 == 0)
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
		if (unitStatus.frameCount % 4 == 0)
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
