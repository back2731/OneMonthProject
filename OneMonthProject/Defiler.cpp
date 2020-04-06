#include "stdafx.h"
#include "Defiler.h"


Defiler::Defiler()
{
}


Defiler::~Defiler()
{
}

Defiler::Defiler(int _playerNumber, POINT birthXY)
{
	progressBar = new ProgressBar;
	unitStatus.unitKind = DEFILER;

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 80;
	unitStatus.unitCurrentHp = 80;
	unitStatus.unitAtk = 0;
	unitStatus.unitDef = 1;
	unitStatus.unitBaseAtk = 0;
	unitStatus.unitBaseDef = 1;
	unitStatus.unitTime = 0;
	unitStatus.unitSpeed = 3;

	unitStatus.unitMineralPrice = 50;
	unitStatus.unitGasPrice = 150;

	unitStatus.unitState = IDLE;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("defiler");
	unitStatus.unitWireFrame = IMAGEMANAGER->FindImage("defilerWirefram");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("2X2");
	unitStatus.unitFrontProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressFront");
	unitStatus.unitBackProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressBack");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth() * 0.25, unitStatus.unitImage->GetFrameHeight() * 0.25);
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) * 0.5;;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) * 0.5;;
	unitStatus.unitSearchingRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, WINSIZEX / 2, WINSIZEY / 2);

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

	unitStatus.unitPortraitsImage = IMAGEMANAGER->FindImage("portraitsDefiler");
	unitStatus.unitPortraitsCount = 0;
	unitStatus.unitPortraitsFrameY = 0;

	isClick = false;
	progressBar->Init("images/UI/ZergUnitProgressFront.bmp", "images/UI/ZergUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);

	InitAstar();
	SetBlock();

	// 명령 슬롯 생성
	SetCommandSlot(SLOT1, new MoveCommand);
	SetCommandSlot(SLOT2, new StopCommand);
	SetCommandSlot(SLOT3, new AttackCommand);
	SetCommandSlot(SLOT9, new Burrow);

	// 명령 이미지 설정
	commandImage[SLOT1] = IMAGEMANAGER->FindImage("Move");
	commandImage[SLOT2] = IMAGEMANAGER->FindImage("Stop");
	commandImage[SLOT4] = IMAGEMANAGER->FindImage("Patrol");
	commandImage[SLOT5] = IMAGEMANAGER->FindImage("Hold");
	commandImage[SLOT9] = IMAGEMANAGER->FindImage("EvolveBurrow");

	abilityImage[SLOT1] = IMAGEMANAGER->FindImage("carapace");

	// 슬롯 위치 카메라 반영
	SetCommandRect();
	SetAbilityRect();
}

HRESULT Defiler::Init()
{
	return S_OK;
}

void Defiler::Release()
{
}

void Defiler::Update()
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
			PLAYERMANAGER->SetChangeState(IDLE);
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
	unitStatus.unitRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImageWidthQuarter, unitStatus.unitImageHeightQuarter);
	unitStatus.unitSearchingRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, WINSIZEX / 2, WINSIZEY / 2);

	unitStatus.unitDef = 0 + UPGRADEMANAGER->GetEvolveCarapace();
	unitStatus.unitPositionRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, 2, 2);


}

void Defiler::Render(HDC hdc)
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

void Defiler::RenderUI(HDC hdc)
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
		// 명령 슬롯 이미지 렌더
		commandImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
		commandImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
		commandImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top);
		commandImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
		commandImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);

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
		if (PtInRect(&commandRect[SLOT9], m_ptMouse))
		{
			descriptionImage[SLOT9] = IMAGEMANAGER->FindImage("burrowUI");
			descriptionImage[SLOT9]->Render(hdc, commandRect[SLOT9].left - descriptionImage[SLOT9]->GetWidth() + 50, commandRect[SLOT9].top - descriptionImage[SLOT9]->GetHeight());
		}

		// 능력치 이미지 렌더
		abilityImage[SLOT1]->Render(hdc, abilityRect[SLOT1].left, abilityRect[SLOT1].top);

		SetTextColor(hdc, RGB(0, 222, 0));
		sprintf_s(str, "%d", unitStatus.unitCurrentHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 240, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		sprintf_s(str, "/   %d", unitStatus.unitMaxHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 200, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));

		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(str, "Zerg Defiler");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 80, CAMERAMANAGER->GetCameraCenter().y + 290, str, strlen(str));

		sprintf_s(str, "kills : 0");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 60, CAMERAMANAGER->GetCameraCenter().y + 340, str, strlen(str));

		// 능력치 업그레이드 단계 렌더
		sprintf_s(str, "%d", UPGRADEMANAGER->GetEvolveCarapace());
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 60, CAMERAMANAGER->GetCameraCenter().y + 419, str, strlen(str));

		// 업그레이드 반영 렌더
		HFONT myFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "돋움체");
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);

		if (PtInRect(&abilityRect[SLOT1], m_ptMouse))
		{
			abilityDescriptionImage[SLOT1] = IMAGEMANAGER->FindImage("zergCarapaceUI");
			abilityDescriptionImage[SLOT1]->Render(hdc, abilityRect[SLOT1].right, abilityRect[SLOT1].top);

			sprintf_s(str, "%d + %d", unitStatus.unitBaseDef, UPGRADEMANAGER->GetEvolveCarapace());
			TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x + 42, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		}

		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}
}

void Defiler::PlayAnimation()
{
	if (unitStatus.unitState == IDLE)
	{
		unitStatus.frameCount++;
		if (unitStatus.frameCount % 6 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
			}
			unitStatus.frameIndexX++;
		}
	}

}
