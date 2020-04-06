#include "stdafx.h"
#include "Zergling.h"


Zergling::Zergling()
{
}


Zergling::~Zergling()
{
}

Zergling::Zergling(int _playerNumber, POINT birthXY)
{
	progressBar = new ProgressBar;
	unitStatus.unitKind = ZERGLING;

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 35;
	unitStatus.unitCurrentHp = 35;
	unitStatus.unitAtk = 5;
	unitStatus.unitBaseAtk = 5;
	unitStatus.unitDef = 0;
	unitStatus.unitBaseDef = 0;
	unitStatus.unitTime = 0;
	unitStatus.unitSpeed = 5;
	unitStatus.unitMineralPrice = 50;
	unitStatus.unitGasPrice = 0;
	
	unitStatus.unitState = IDLE;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("zergling");
	unitStatus.enemyUnitImage1 = IMAGEMANAGER->FindImage("enemyZergling");
	unitStatus.unitWireFrame = IMAGEMANAGER->FindImage("zerglingWirefram");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("1X1");
	unitStatus.enemyUnitSelectImage = IMAGEMANAGER->FindImage("enemy1X1");
	unitStatus.unitFrontProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressFront");
	unitStatus.unitBackProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressBack");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth() * 0.25, unitStatus.unitImage->GetFrameHeight() * 0.25);
	unitStatus.unitAtkRect = RectMakeCenter(birthXY.x, birthXY.y, 3, 3);
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) * 0.5;;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) * 0.5;;
	unitStatus.unitSearchingRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImage->GetFrameWidth(), unitStatus.unitImage->GetFrameHeight());

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

	unitStatus.unitPortraitsImage = IMAGEMANAGER->FindImage("portraitsZergling");
	unitStatus.unitPortraitsCount = 0;
	unitStatus.unitPortraitsFrameY = 0;

	isClick = false;
	progressBar->Init("images/UI/ZergUnitProgressFront.bmp", "images/UI/ZergUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);

	InitAstar();
	SetBlock();

	// ��� ���� ����
	SetCommandSlot(SLOT1, new MoveCommand);
	SetCommandSlot(SLOT2, new StopCommand);
	SetCommandSlot(SLOT3, new AttackCommand);
	SetCommandSlot(SLOT4, new PatrolCommand);
	SetCommandSlot(SLOT5, new HoldCommand);
	SetCommandSlot(SLOT9, new Burrow);

	// ��� �̹��� ����
	commandImage[SLOT1] = IMAGEMANAGER->FindImage("Move");
	commandImage[SLOT2] = IMAGEMANAGER->FindImage("Stop");
	commandImage[SLOT3] = IMAGEMANAGER->FindImage("Attack");
	commandImage[SLOT4] = IMAGEMANAGER->FindImage("Patrol");
	commandImage[SLOT5] = IMAGEMANAGER->FindImage("Hold");
	commandImage[SLOT9] = IMAGEMANAGER->FindImage("EvolveBurrow");
	
	abilityImage[SLOT1] = IMAGEMANAGER->FindImage("carapace");
	abilityImage[SLOT2] = IMAGEMANAGER->FindImage("claws");

	// ���� ��ġ ī�޶� �ݿ�
	SetCommandRect();
	SetAbilityRect();
}

HRESULT Zergling::Init()
{
	return S_OK;
}

void Zergling::Release()
{
}

void Zergling::Update()
{
	progressBar->SetGauge(unitStatus.unitCurrentHp, unitStatus.unitMaxHp);

	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		{
			// ���ȴٴ� ����� true ���ִ� ���� �����.
			PLAYERMANAGER->SetInputCommandMove(true);
			// ��ġ�ϴ� �ش� ��ġ�� �������ش�.
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
			// ����� ������ �� A*�� ���� ���� �ʱ�ȭ���ְ� ����bool������ true�� �ٲ��ش�
			SetEndTile();
			SetAstarVector();
			SetStartTile();
			PLAYERMANAGER->SetChangeState(MOVE);
			unitStatus.unitState = PLAYERMANAGER->GetChangeState();
		}
	}

	// �ִϸ��̼��� �������� ������.
	PlayAnimation();
	PlayPortraits();

	if (isSearch)
	{
		//PLAYERMANAGER->SetChangeState(ATTACK);
		//unitStatus.unitState = PLAYERMANAGER->GetChangeState();
	}
	else
	{
		// A*����
		UpdateAstar(unitStatus.unitRectX, unitStatus.unitRectY);

		// ���ϴ� ������ ���� �������� �ٲ��ش�.
		unitStatus.frameIndexY = ChangeImageFrame();

		// ��ã�⸦ ���� ������ �̵��Ѵ�.
		MoveUnit(unitStatus.unitSpeed);
	}

	if (IntersectRect(&tempRect, &_tileMap[PLAYERMANAGER->GetSaveUnitPosition()].rect, &unitStatus.unitRect))
	{
		PLAYERMANAGER->SetChangeState(IDLE);
		unitStatus.unitState = PLAYERMANAGER->GetChangeState();
	}

	// ���� ��Ʈ�� �缳�����ش�.
	unitStatus.unitRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImageWidthQuarter, unitStatus.unitImageHeightQuarter);
	unitStatus.unitSearchingRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, WINSIZEX / 2, WINSIZEY / 2);
	unitStatus.unitAtkRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, 1, 1);

	if (unitStatus.unitState == ATTACK)
	{
		conutTest++;
		if (conutTest % 30 == 0)
		{
			if (unitStatus.frameIndexY == DIRECTION_UP)
			{
				unitStatus.unitAtkRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY - 30, 15, 15);
			}
			if (unitStatus.frameIndexY == DIRECTION_RIGHT)
			{
				unitStatus.unitAtkRect = RectMakeCenter(unitStatus.unitRectX - 30, unitStatus.unitRectY, 15, 15);
			}
			if (unitStatus.frameIndexY == DIRECTION_LEFT)
			{
				unitStatus.unitAtkRect = RectMakeCenter(unitStatus.unitRectX + 30, unitStatus.unitRectY, 15, 15);
			}
			if (unitStatus.frameIndexY == DIRECTION_DOWN)
			{
				unitStatus.unitAtkRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY + 30, 15, 15);
			}
			if (unitStatus.frameIndexY == DIRECTION_LEFTUP)
			{
				unitStatus.unitAtkRect = RectMakeCenter(unitStatus.unitRectX + 30, unitStatus.unitRectY - 30, 15, 15);
			}
			if (unitStatus.frameIndexY == DIRECTION_RIGHTDOWN)
			{
				unitStatus.unitAtkRect = RectMakeCenter(unitStatus.unitRectX + 30, unitStatus.unitRectY + 30, 15, 15);
			}
			if (unitStatus.frameIndexY == DIRECTION_LEFTDOWN)
			{
				unitStatus.unitAtkRect = RectMakeCenter(unitStatus.unitRectX - 30, unitStatus.unitRectY + 30, 15, 15);
			}
			if (unitStatus.frameIndexY == DIRECTION_RIGHTUP)
			{
				unitStatus.unitAtkRect = RectMakeCenter(unitStatus.unitRectX - 30, unitStatus.unitRectY - 30, 15, 15);
			}
		}		
	}

	unitStatus.unitAtk = 5 + UPGRADEMANAGER->GetMeleeAttack();
	unitStatus.unitDef = 0 + UPGRADEMANAGER->GetEvolveCarapace();
	unitStatus.unitPositionRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, 2, 2);

}

void Zergling::Render(HDC hdc)
{
	if (KEYMANAGER->IsToggleKey(VK_MBUTTON))
	{
		HBRUSH myBrush, oldBrush;
		HPEN myPen, oldPen;

		myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		myPen = CreatePen(PS_SOLID, 2, RGB(0, 222, 0));
		oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, unitStatus.unitSearchingRect.left, unitStatus.unitSearchingRect.top, unitStatus.unitSearchingRect.right, unitStatus.unitSearchingRect.bottom);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		unitStatus.unitSelectImage->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitSelectImageWidth, unitStatus.unitRectY - unitStatus.unitSelectImageHeight);
		progressBar->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitProgressWidth, unitStatus.unitRectY + 20);
	}
	if (isClick && unitStatus.playerNumber == PLAYER2)
	{
		unitStatus.unitSelectImage->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitSelectImageWidth, unitStatus.unitRectY - unitStatus.unitSelectImageHeight);
		progressBar->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitProgressWidth, unitStatus.unitRectY + 20);
	}

	if (unitStatus.playerNumber == PLAYER1)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImageWidthHalf,
			unitStatus.unitRectY - unitStatus.unitImageHeightHalf, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (unitStatus.playerNumber == PLAYER2)
	{
		unitStatus.enemyUnitImage1->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImageWidthHalf,
			unitStatus.unitRectY - unitStatus.unitImageHeightHalf, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
}

void Zergling::RenderUI(HDC hdc)
{	
	// ���� ��ġ ī�޶� �ݿ�
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
				Rectangle(hdc, abilityRect[i].left, abilityRect[i].top, abilityRect[i].right, abilityRect[i].bottom);
			}
		}

		// ��� ���� �̹��� ����
		commandImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
		commandImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
		commandImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
		commandImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top);
		commandImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
		commandImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);

		// ��� ���� ���� ����
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
		if (PtInRect(&commandRect[SLOT3], m_ptMouse))
		{
			descriptionImage[SLOT3] = IMAGEMANAGER->FindImage("AttackUI");
			descriptionImage[SLOT3]->Render(hdc, commandRect[SLOT3].left - descriptionImage[SLOT3]->GetWidth() + 50, commandRect[SLOT3].bottom);
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
		
		// �ɷ�ġ �̹��� ����
		abilityImage[SLOT1]->Render(hdc, abilityRect[SLOT1].left, abilityRect[SLOT1].top);
		abilityImage[SLOT2]->Render(hdc, abilityRect[SLOT2].left, abilityRect[SLOT2].top);

		SetTextColor(hdc, RGB(0, 222, 0));
		sprintf_s(str, "%d", unitStatus.unitCurrentHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 240, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		sprintf_s(str, "/   %d", unitStatus.unitMaxHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 200, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));

		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(str, "Zerg Zergling");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 80, CAMERAMANAGER->GetCameraCenter().y + 290, str, strlen(str));

		sprintf_s(str, "kills : 0");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 60, CAMERAMANAGER->GetCameraCenter().y + 340, str, strlen(str));
		
		// �ɷ�ġ ���׷��̵� �ܰ� ����
		sprintf_s(str, "%d", UPGRADEMANAGER->GetEvolveCarapace());
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 60, CAMERAMANAGER->GetCameraCenter().y + 419, str, strlen(str));

		sprintf_s(str, "%d", UPGRADEMANAGER->GetMeleeAttack());
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x + 10, CAMERAMANAGER->GetCameraCenter().y + 419, str, strlen(str));
		
		// ���׷��̵� �ݿ� ����
		HFONT myFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "����ü");
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);

		if (PtInRect(&abilityRect[SLOT1], m_ptMouse))
		{
			abilityDescriptionImage[SLOT1] = IMAGEMANAGER->FindImage("zergCarapaceUI");
			abilityDescriptionImage[SLOT1]->Render(hdc, abilityRect[SLOT1].right, abilityRect[SLOT1].top);

			sprintf_s(str, "%d + %d", unitStatus.unitBaseDef, UPGRADEMANAGER->GetEvolveCarapace());
			TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x + 42, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		}
		if (PtInRect(&abilityRect[SLOT2], m_ptMouse))
		{
			abilityDescriptionImage[SLOT2] = IMAGEMANAGER->FindImage("clawsUI");
			abilityDescriptionImage[SLOT2]->Render(hdc, abilityRect[SLOT2].right, abilityRect[SLOT2].top);

			sprintf_s(str, "%d + %d", unitStatus.unitBaseAtk, UPGRADEMANAGER->GetMeleeAttack());
			TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x + 129, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		}
		
		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}
}

void Zergling::PlayAnimation()
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


