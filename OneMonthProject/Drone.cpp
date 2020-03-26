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
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("2X2");
	unitStatus.unitFrontProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressFront");
	unitStatus.unitBackProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressBack");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth() * 0.25, unitStatus.unitImage->GetFrameHeight() * 0.25);
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
	unitStatus.frameIndexY = 5;

	isClick = false;
	progressBar->Init("images/UI/ZergUnitProgressFront.bmp", "images/UI/ZergUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);
		
	InitAstar();
	SetBlock();

	// ��� ���� ����
	SetCommandSlot(SLOT1, new MoveCommand);
	SetCommandSlot(SLOT2, new StopCommand);
	SetCommandSlot(SLOT3, new AttackCommand);
	SetCommandSlot(SLOT5, new Gathering);
	SetCommandSlot(SLOT7, new BaseBuilding);
	SetCommandSlot(SLOT8, new HighBuilding);
	SetCommandSlot(SLOT9, new Burrow);
	
	// ��� �̹��� ����
	commandImage[SLOT1] = IMAGEMANAGER->FindImage("Move");
	commandImage[SLOT2] = IMAGEMANAGER->FindImage("Stop");
	commandImage[SLOT3] = IMAGEMANAGER->FindImage("Attack");
	commandImage[SLOT5] = IMAGEMANAGER->FindImage("Gathering");
	commandImage[SLOT7] = IMAGEMANAGER->FindImage("BaseBuilding");
	commandImage[SLOT8] = IMAGEMANAGER->FindImage("HighBuilding");
	commandImage[SLOT9] = IMAGEMANAGER->FindImage("EvolveBurrow");

	baseBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("HatcheryUI");
	baseBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("CreepColonyUI");
	baseBuildingImage[SLOT3] = IMAGEMANAGER->FindImage("ExtractorUI");
	baseBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("SpawningPoolUI");
	baseBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("EvolutionChamberUI");
	baseBuildingImage[SLOT7] = IMAGEMANAGER->FindImage("HydraliskDenUI");
	baseBuildingImage[SLOT9] = IMAGEMANAGER->FindImage("Cancel");
	
	highBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("SpireUI");
	highBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("QueensNestUI");
	highBuildingImage[SLOT3] = IMAGEMANAGER->FindImage("NydusCanalUI");
	highBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("UltraliskCavernUI");
	highBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("DefilerMoundUI");
	highBuildingImage[SLOT9] = IMAGEMANAGER->FindImage("Cancel");

	baseBuildingSlot[SLOT1] = new BuildHatchery;
	baseBuildingSlot[SLOT2] = new BuildCreepColony;
	baseBuildingSlot[SLOT3] = new BuildExtractor;
	baseBuildingSlot[SLOT4] = new BuildSpawningPool;
	baseBuildingSlot[SLOT5] = new BuildEvolutionChamber;
	baseBuildingSlot[SLOT7] = new BuildHydraliskDen;
	//baseBuildingSlot[SLOT9] = IMAGEMANAGER->FindImage("Cancel");

	highBuildingSlot[SLOT1] = new BuildSpire;
	highBuildingSlot[SLOT2] = new BuildQueensNest;
	//highBuildingSlot[SLOT3] = IMAGEMANAGER->FindImage("NydusCanalUI");
	//highBuildingSlot[SLOT4] = IMAGEMANAGER->FindImage("UltraliskCavernUI");
	//highBuildingSlot[SLOT5] = IMAGEMANAGER->FindImage("DefilerMoundUI");
	//highBuildingSlot[SLOT9] = IMAGEMANAGER->FindImage("Cancel");

	baseUIrender = true;
	baseBuildingUIrender = false;
	highBuildingUIrender = false;

	greenRectImage = IMAGEMANAGER->FindImage("Green");
	redRectImage = IMAGEMANAGER->FindImage("Red");

	mutateHatcheryImage = IMAGEMANAGER->FindImage("mutateHatchery");
	mutateSpawningPoolImage = IMAGEMANAGER->FindImage("mutateSpawningPool");
	mutateHydraliskDenImage = IMAGEMANAGER->FindImage("mutateHydraliskDen");
	mutateEvolutionChamberImage = IMAGEMANAGER->FindImage("mutateEvolutionChamber");
	mutateCreepColonyImage = IMAGEMANAGER->FindImage("mutateCreepColony");
	mutateExtractorImage = IMAGEMANAGER->FindImage("mutateExtractor");
	
	mutateSpireImage = IMAGEMANAGER->FindImage("mutateSpire");
	mutateQueensNestImage = IMAGEMANAGER->FindImage("mutateQueensNest");

	// ���� ��ġ ī�޶� �ݿ�
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

	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		{
			// ���ȴٴ� ����� true ���ִ� ���� �����.
			PLAYERMANAGER->SetInputCommandMove(true);
		}

		if (PLAYERMANAGER->GetInputCommandMove())
		{
			// ����� ������ �� A*�� ���� ���� �ʱ�ȭ���ְ� ����bool������ true�� �ٲ��ش�
			SetEndTile();
			SetAstarVector();
			SetStartTile();
		}

		if (baseUIrender)
		{
			// �⺻ ���� �������� ����
			if (PtInRect(&commandRect[SLOT7], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					baseUIrender = false;
					baseBuildingUIrender = true;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('B'))
			{
				baseUIrender = false;
				baseBuildingUIrender = true;
			}

			// ���� ���� �������� ����
			if (PtInRect(&commandRect[SLOT8], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					baseUIrender = false;
					highBuildingUIrender = true;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('V'))
			{
				baseUIrender = false;
				highBuildingUIrender = true;
			}
		}
		if (baseBuildingUIrender)
		{
			// ��ó��
			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					mutateHatchery = true;

					mutateEvolutionChamber = false;
					mutateHydraliskDen = false;
					mutateSpawningPool = false;
					mutateCreepColony = false;
					mutateExtractor = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('H'))
			{
				mutateHatchery = true;

				mutateEvolutionChamber = false;
				mutateHydraliskDen = false;
				mutateSpawningPool = false;
				mutateCreepColony = false;
				mutateExtractor = false;
			}

			// ũ�� �ݷδ�
			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					mutateCreepColony = true;

					mutateHatchery = false;
					mutateSpawningPool = false;
					mutateHydraliskDen = false;
					mutateEvolutionChamber = false;
					mutateExtractor = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('C'))
			{
				mutateCreepColony = true;

				mutateHatchery = false;
				mutateSpawningPool = false;
				mutateHydraliskDen = false;
				mutateEvolutionChamber = false;
				mutateExtractor = false;
			}

			// �ͽ�Ʈ����
			if (PtInRect(&commandRect[SLOT3], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					mutateExtractor = true;

					mutateHatchery = false;
					mutateSpawningPool = false;
					mutateHydraliskDen = false;
					mutateEvolutionChamber = false;
					mutateCreepColony = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('E'))
			{
				mutateExtractor = true;

				mutateHatchery = false;
				mutateSpawningPool = false;
				mutateHydraliskDen = false;
				mutateEvolutionChamber = false;
				mutateCreepColony = false;
			}

			// ������Ǯ
			if (PtInRect(&commandRect[SLOT4], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					mutateSpawningPool = true;

					mutateHatchery = false;
					mutateEvolutionChamber = false;
					mutateHydraliskDen = false;
					mutateCreepColony = false;
					mutateExtractor = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('S'))
			{
				mutateSpawningPool = true;				
				
				mutateHatchery = false;
				mutateEvolutionChamber = false;
				mutateHydraliskDen = false;
				mutateCreepColony = false;
				mutateExtractor = false;

			}

			// �������è��
			if (PtInRect(&commandRect[SLOT5], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					mutateEvolutionChamber = true;

					mutateHatchery = false;
					mutateSpawningPool = false;
					mutateHydraliskDen = false;
					mutateCreepColony = false;
					mutateExtractor = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('V'))
			{
				mutateEvolutionChamber = true;

				mutateHatchery = false;
				mutateSpawningPool = false;
				mutateHydraliskDen = false;
				mutateCreepColony = false;
				mutateExtractor = false;
			}

			// ����󸮽�ũ��
			if (PtInRect(&commandRect[SLOT7], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					mutateHydraliskDen = true;
					
					mutateHatchery = false;
					mutateSpawningPool = false;
					mutateEvolutionChamber = false;
					mutateCreepColony = false;
					mutateExtractor = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('D'))
			{
				mutateHydraliskDen = true;

				mutateHatchery = false;
				mutateSpawningPool = false;
				mutateEvolutionChamber = false;
				mutateCreepColony = false;
				mutateExtractor = false;
			}

			// �ڷΰ���
			if (PtInRect(&commandRect[SLOT9], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					baseUIrender = true;
					baseBuildingUIrender = false;
					
					mutateHatchery = false;
					mutateSpawningPool = false;
					mutateHydraliskDen = false;
					mutateEvolutionChamber = false;
					mutateCreepColony = false;
					mutateExtractor = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
			{
				baseUIrender = true;
				baseBuildingUIrender = false;

				mutateHatchery = false;
				mutateSpawningPool = false;
				mutateHydraliskDen = false;
				mutateEvolutionChamber = false;
				mutateCreepColony = false;
				mutateExtractor = false;
			}
		}
		if (highBuildingUIrender)
		{
			// �����̾�
			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					mutateSpire = true;

					mutateQueensNest = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('S'))
			{
				mutateSpire = true;

				mutateQueensNest = false;
			}

			// ����׽�Ʈ
			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					mutateQueensNest = true;

					mutateSpire = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('Q'))
			{
				mutateQueensNest = true;

				mutateSpire = false;
			}

			if (PtInRect(&commandRect[SLOT9], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					baseUIrender = true;
					highBuildingUIrender = false;

					mutateSpire = false;
					mutateQueensNest = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
			{
				baseUIrender = true;
				highBuildingUIrender = false;
				mutateSpire = false;
				mutateQueensNest = false;
			}
		}
	}
	else
	{
		baseUIrender = true;
		baseBuildingUIrender = false;
		highBuildingUIrender = false;
	}

	if (mutateHatchery)
	{
		mutateSpawningPool = false;
		mutateHydraliskDen = false;
		mutateEvolutionChamber = false;
		mutateCreepColony = false;
		mutateExtractor = false;
		mutateSpire = false;
		mutateQueensNest = false;

		// �ش� ��Ұ� ��ġ ������ ��������� Ÿ���� Block������ �Ǻ��� �����صд�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				for (int j = 0; j < TILESIZE; j++)
				{
					if (IntersectRect(&temp, &mutateRect.buildRect[i], &_tileMap[j].rect))
					{
						if (_tileMap[j].block)
						{
							mutateRect.choiceColor[i] = true;
						}
						else
						{
							mutateRect.choiceColor[i] = false;
						}
					}
				}
			}
		}

		// ��ġ��� ���¿����� ��ɹ�
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// ��ġ�� ������ ��
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// ��ġ�ϴ� �ش� ��ġ�� �������ش�.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateHatchery = false;
				baseBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveHatchery = true;
			}
			// ��ġ�� �Ұ��� ��
			else
			{
				mutateHatchery = true;
				isClick = true;
				// ��ġ�Ұ� �޽����� ����� ����
			}
		}
	}

	if (mutateSpawningPool)
	{
		mutateHatchery = false;
		mutateHydraliskDen = false;
		mutateEvolutionChamber = false;
		mutateCreepColony = false;
		mutateExtractor = false;
		mutateSpire = false;
		mutateQueensNest = false;

		// �ش� ��Ұ� ��ġ ������ ��������� Ÿ���� Block������ �Ǻ��� �����صд�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				for (int j = 0; j < TILESIZE; j++)
				{
					if (IntersectRect(&temp, &mutateRect.buildRect[i], &_tileMap[j].rect))
					{
						if (i == 3) continue;
						if (i == 7) continue;
						if (i == 8) continue;
						if (i == 9) continue;
						if (i == 10) continue;
						if (i == 11) continue;
						if (_tileMap[j].block)
						{
							mutateRect.choiceColor[i] = true;
						}
						else
						{
							mutateRect.choiceColor[i] = false;
						}
					}
				}
			}
		}

		// ��ġ��� ���¿����� ��ɹ�
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// ��ġ�� ������ ��
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// ��ġ�ϴ� �ش� ��ġ�� �������ش�.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateSpawningPool = false;
				baseBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveSpawningPool = true;
			}
			// ��ġ�� �Ұ��� ��
			else
			{
				mutateSpawningPool = true;
				isClick = true;
				// ��ġ�Ұ� �޽����� ����� ����
			}
		}
	}

	if (mutateHydraliskDen)
	{
		mutateHatchery = false;
		mutateSpawningPool = false;
		mutateEvolutionChamber = false;
		mutateCreepColony = false;
		mutateExtractor = false;
		mutateSpire = false;
		mutateQueensNest = false;

		// �ش� ��Ұ� ��ġ ������ ��������� Ÿ���� Block������ �Ǻ��� �����صд�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				for (int j = 0; j < TILESIZE; j++)
				{
					if (IntersectRect(&temp, &mutateRect.buildRect[i], &_tileMap[j].rect))
					{
						if (i == 3) continue;
						if (i == 7) continue;
						if (i == 8) continue;
						if (i == 9) continue;
						if (i == 10) continue;
						if (i == 11) continue;
						if (_tileMap[j].block)
						{
							mutateRect.choiceColor[i] = true;
						}
						else
						{
							mutateRect.choiceColor[i] = false;
						}
					}
				}
			}
		}

		// ��ġ��� ���¿����� ��ɹ�
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// ��ġ�� ������ ��
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// ��ġ�ϴ� �ش� ��ġ�� �������ش�.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateHydraliskDen = false;
				baseBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveHydraliskDen = true;
			}
			// ��ġ�� �Ұ��� ��
			else
			{
				mutateHydraliskDen = true;
				isClick = true;
				// ��ġ�Ұ� �޽����� ����� ����
			}
		}
	}

	if (mutateEvolutionChamber)
	{
		mutateHatchery = false;
		mutateSpawningPool = false;
		mutateHydraliskDen = false;
		mutateCreepColony = false;
		mutateExtractor = false;
		mutateSpire = false;
		mutateQueensNest = false;

		// �ش� ��Ұ� ��ġ ������ ��������� Ÿ���� Block������ �Ǻ��� �����صд�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				for (int j = 0; j < TILESIZE; j++)
				{
					if (IntersectRect(&temp, &mutateRect.buildRect[i], &_tileMap[j].rect))
					{
						if (i == 3) continue;
						if (i == 7) continue;
						if (i == 8) continue;
						if (i == 9) continue;
						if (i == 10) continue;
						if (i == 11) continue;
						if (_tileMap[j].block)
						{
							mutateRect.choiceColor[i] = true;
						}
						else
						{
							mutateRect.choiceColor[i] = false;
						}
					}
				}
			}
		}

		// ��ġ��� ���¿����� ��ɹ�
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// ��ġ�� ������ ��
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// ��ġ�ϴ� �ش� ��ġ�� �������ش�.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateEvolutionChamber = false;
				baseBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveEvolutionChamber = true;
			}
			// ��ġ�� �Ұ��� ��
			else
			{
				mutateEvolutionChamber = true;
				isClick = true;
				// ��ġ�Ұ� �޽����� ����� ����
			}
		}
	}

	if (mutateCreepColony)
	{
		mutateHatchery = false;
		mutateSpawningPool = false;
		mutateHydraliskDen = false;
		mutateEvolutionChamber = false;
		mutateExtractor = false;
		mutateSpire = false;
		mutateQueensNest = false;

		// �ش� ��Ұ� ��ġ ������ ��������� Ÿ���� Block������ �Ǻ��� �����صд�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				for (int j = 0; j < TILESIZE; j++)
				{
					if (IntersectRect(&temp, &mutateRect.buildRect[i], &_tileMap[j].rect))
					{
						if (i == 2) continue;
						if (i == 3) continue;
						if (i == 6) continue;
						if (i == 7) continue;
						if (i == 8) continue;
						if (i == 9) continue;
						if (i == 10) continue;
						if (i == 11) continue;
						if (_tileMap[j].block)
						{
							mutateRect.choiceColor[i] = true;
						}
						else
						{
							mutateRect.choiceColor[i] = false;
						}
					}
				}
			}
		}

		// ��ġ��� ���¿����� ��ɹ�
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// ��ġ�� ������ ��
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// ��ġ�ϴ� �ش� ��ġ�� �������ش�.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateCreepColony = false;
				baseBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveCreepColony = true;
			}
			// ��ġ�� �Ұ��� ��
			else
			{
				mutateCreepColony = true;
				isClick = true;
				// ��ġ�Ұ� �޽����� ����� ����
			}
		}
	}

	if (mutateExtractor)
	{
		mutateHatchery = false;
		mutateSpawningPool = false;
		mutateHydraliskDen = false;
		mutateEvolutionChamber = false;
		mutateCreepColony = false;
		mutateSpire = false;
		mutateQueensNest = false;

		// �ش� ��Ұ� ��ġ ������ ��������� Ÿ���� Block������ �Ǻ��� �����صд�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				for (int j = 0; j < TILESIZE; j++)
				{
					if (IntersectRect(&temp, &mutateRect.buildRect[i], &_tileMap[j].rect))
					{
						if (i == 8) continue;
						if (i == 9) continue;
						if (i == 10) continue;
						if (i == 11) continue;
						if (_tileMap[j].gas)
						{
							mutateRect.choiceColor[i] = false;
						}
						else
						{
							mutateRect.choiceColor[i] = true;
						}
					}
				}
			}
		}

		// ��ġ��� ���¿����� ��ɹ�
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// ��ġ�� ������ ��
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// ��ġ�ϴ� �ش� ��ġ�� �������ش�.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateExtractor = false;
				baseBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveExtractor = true;
			}
			// ��ġ�� �Ұ��� ��
			else
			{
				mutateExtractor = true;
				isClick = true;
				// ��ġ�Ұ� �޽����� ����� ����
			}
		}
	}

	if (mutateSpire)
	{
		mutateHatchery = false;
		mutateSpawningPool = false;
		mutateHydraliskDen = false;
		mutateEvolutionChamber = false;
		mutateCreepColony = false;
		mutateExtractor = false;
		mutateQueensNest = false;

		// �ش� ��Ұ� ��ġ ������ ��������� Ÿ���� Block������ �Ǻ��� �����صд�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				for (int j = 0; j < TILESIZE; j++)
				{
					if (IntersectRect(&temp, &mutateRect.buildRect[i], &_tileMap[j].rect))
					{
						if (i == 2) continue;
						if (i == 3) continue;
						if (i == 6) continue;
						if (i == 7) continue;
						if (i == 8) continue;
						if (i == 9) continue;
						if (i == 10) continue;
						if (i == 11) continue;
						if (_tileMap[j].block)
						{
							mutateRect.choiceColor[i] = true;
						}
						else
						{
							mutateRect.choiceColor[i] = false;
						}
					}
				}
			}
		}

		// ��ġ��� ���¿����� ��ɹ�
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// ��ġ�� ������ ��
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// ��ġ�ϴ� �ش� ��ġ�� �������ش�.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateSpire = false;
				highBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveSpire = true;
			}
			// ��ġ�� �Ұ��� ��
			else
			{
				mutateSpire = true;
				isClick = true;
				// ��ġ�Ұ� �޽����� ����� ����
			}
		}
	}

	if (mutateQueensNest)
	{
		mutateHatchery = false;
		mutateHydraliskDen = false;
		mutateEvolutionChamber = false;
		mutateCreepColony = false;
		mutateExtractor = false;
		mutateSpire = false;
		mutateSpawningPool = false;

		// �ش� ��Ұ� ��ġ ������ ��������� Ÿ���� Block������ �Ǻ��� �����صд�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				for (int j = 0; j < TILESIZE; j++)
				{
					if (IntersectRect(&temp, &mutateRect.buildRect[i], &_tileMap[j].rect))
					{
						if (i == 3) continue;
						if (i == 7) continue;
						if (i == 8) continue;
						if (i == 9) continue;
						if (i == 10) continue;
						if (i == 11) continue;
						if (_tileMap[j].block)
						{
							mutateRect.choiceColor[i] = true;
						}
						else
						{
							mutateRect.choiceColor[i] = false;
						}
					}
				}
			}
		}

		// ��ġ��� ���¿����� ��ɹ�
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// ��ġ�� ������ ��
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// ��ġ�ϴ� �ش� ��ġ�� �������ش�.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateQueensNest = false;
				highBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveQueensNest = true;
			}
			// ��ġ�� �Ұ��� ��
			else
			{
				mutateQueensNest = true;
				isClick = true;
				// ��ġ�Ұ� �޽����� ����� ����
			}
		}
	}

	// ��ġ ��ҿ� �������� �� ���»��·� �̹����� �ٲ��ش�.
	if (IntersectRect(&temp, &_tileMap[saveUnitPosition].rect, &unitStatus.unitRect))
	{
		if (isArriveHatchery)
		{
			isTransHatchery = true;
			isArriveHatchery = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		if (isArriveSpawningPool)
		{
			isTransSpawningPool = true;
			isArriveSpawningPool = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		if (isArriveHydraliskDen)
		{
			isTransHydraliskDen = true;
			isArriveHydraliskDen = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		if (isArriveEvolutionChamber)
		{
			isTransEvolutionChamber = true;
			isArriveEvolutionChamber = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		if (isArriveCreepColony)
		{
			isTransCreepColony = true;
			isArriveCreepColony = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthSmall");
		}
		if (isArriveExtractor)
		{
			isTransExtractor = true;
			isArriveExtractor = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthBig");
		}
		if (isArriveSpire)
		{
			isTransSpire = true;
			isArriveSpire = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		if (isArriveQueensNest)
		{
			isTransQueensNest = true;
			isArriveQueensNest = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
	}

	// �ִϸ��̼��� �������� ������.
	PlayAnimation();

	// ���»��°� �ƴҶ� �����ϴ� �κ�.
	if (CheckMutate())
	{
		// A*����
		UpdateAstar(unitStatus.unitRectX, unitStatus.unitRectY);

		// ���ϴ� ������ ���� �������� �ٲ��ش�.
		unitStatus.frameIndexY = ChangeImageFrame();

		// ��ã�⸦ ���� ������ �̵��Ѵ�.
		MoveUnit();

		// ���� ��Ʈ�� �缳�����ش�.
		unitStatus.unitRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImageWidthQuarter, unitStatus.unitImageHeightQuarter);
	}

	buildRectRender = RectMake(m_ptMouse.x, m_ptMouse.y, CELL_WIDTH * 4, CELL_HEIGHT * 3);
}

void Drone::Render(HDC hdc)
{
	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		unitStatus.unitSelectImage->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitSelectImageWidth, unitStatus.unitRectY - unitStatus.unitSelectImageHeight);
		progressBar->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitProgressWidth, unitStatus.unitRectY + 40);
	}
	if (isTransHatchery)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX * 2].rect.left + 40, _tileMap[saveUnitPosition - 2].rect.top,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if(isTransSpawningPool)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX * 2].rect.left, _tileMap[saveUnitPosition - 2].rect.top - 30,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransHydraliskDen)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX * 2].rect.left, _tileMap[saveUnitPosition - 2].rect.top - 30,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransEvolutionChamber)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX * 2].rect.left, _tileMap[saveUnitPosition - 2].rect.top - 30,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransCreepColony)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX * 2].rect.left - 30, _tileMap[saveUnitPosition - 2].rect.top - 20,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransExtractor)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX * 1].rect.left- 30, _tileMap[saveUnitPosition - 3].rect.top-10,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransSpire)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX * 2].rect.left - 30, _tileMap[saveUnitPosition - 2].rect.top - 30,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransQueensNest)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX * 2].rect.left, _tileMap[saveUnitPosition - 2].rect.top - 30,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}	
	else
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImageWidthHalf,
			unitStatus.unitRectY - unitStatus.unitImageHeightHalf, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}

	if (mutateHatchery)
	{
		// ���콺 ����Ʈ�� ��ó�� �̹���
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateHatcheryImage->AlphaRender(hdc, _tileMap[i].left, _tileMap[i].top, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j*4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// ��ġ ���� ���ο� ���� ���� �������ش�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				if (mutateRect.choiceColor[i])
				{
					redRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
				else
				{
					greenRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
			}
		}
	}

	if (mutateSpawningPool)
	{
		// ���콺 ����Ʈ�� ������Ǯ �̹���
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateSpawningPoolImage->AlphaRender(hdc, _tileMap[i].left, _tileMap[i].top, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// ��ġ ���� ���ο� ���� ���� �������ش�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				if (i == 3) continue;
				if (i == 7) continue;
				if (i == 8) continue;
				if (i == 9) continue;
				if (i == 10) continue;
				if (i == 11) continue;
				if (mutateRect.choiceColor[i])
				{
					redRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
				else
				{
					greenRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
			}
		}
	}

	if (mutateHydraliskDen)
	{
		// ���콺 ����Ʈ�� ����󸮽�ũ�� �̹���
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateHydraliskDenImage->AlphaRender(hdc, _tileMap[i].left, _tileMap[i].top - 40, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// ��ġ ���� ���ο� ���� ���� �������ش�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				if (i == 3) continue;
				if (i == 7) continue;
				if (i == 8) continue;
				if (i == 9) continue;
				if (i == 10) continue;
				if (i == 11) continue;
				if (mutateRect.choiceColor[i])
				{
					redRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
				else
				{
					greenRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
			}
		}
	}

	if (mutateEvolutionChamber)
	{
		// ���콺 ����Ʈ�� ������� è�� �̹���
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateEvolutionChamberImage->AlphaRender(hdc, _tileMap[i].left - 30, _tileMap[i].top - 40, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// ��ġ ���� ���ο� ���� ���� �������ش�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				if (i == 3) continue;
				if (i == 7) continue;
				if (i == 8) continue;
				if (i == 9) continue;
				if (i == 10) continue;
				if (i == 11) continue;
				if (mutateRect.choiceColor[i])
				{
					redRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
				else
				{
					greenRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
			}
		}
	}
	
	if (mutateCreepColony)
	{
		// ���콺 ����Ʈ�� ũ�� �ݷδ� �̹���
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateCreepColonyImage->AlphaRender(hdc, _tileMap[i].left - 20, _tileMap[i].top, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// ��ġ ���� ���ο� ���� ���� �������ش�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				if (i == 2) continue;
				if (i == 3) continue;
				if (i == 6) continue;
				if (i == 7) continue;
				if (i == 8) continue;
				if (i == 9) continue;
				if (i == 10) continue;
				if (i == 11) continue;
				if (mutateRect.choiceColor[i])
				{
					redRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
				else
				{
					greenRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
			}
		}
	}
	
	if (mutateExtractor)
	{
		// ���콺 ����Ʈ�� �ͽ�Ʈ���� �̹���
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{

				mutateExtractorImage->AlphaRender(hdc, _tileMap[i].left, _tileMap[i].top - 128, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}	
		}

		for (int i = 0; i < TILESIZE; i++)
		{
			if (_tileMap[i].gas)
			{
				mutateExtractorImage->AlphaRender(hdc, _tileMap[i].left, _tileMap[i].top - 128, ALPHA);
				break;
			}
		}

		// ��ġ ���� ���ο� ���� ���� �������ش�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				if (i == 8) continue;
				if (i == 9) continue;
				if (i == 10) continue;
				if (i == 11) continue;
				if (mutateRect.choiceColor[i])
				{
					redRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
				else
				{
					greenRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
			}
		}
	}

	if (mutateSpire)
	{
		// ���콺 ����Ʈ�� �����̾� �̹���
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateSpireImage->AlphaRender(hdc, _tileMap[i].left - 64, _tileMap[i].top - 80, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// ��ġ ���� ���ο� ���� ���� �������ش�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				if (i == 2) continue;
				if (i == 3) continue;
				if (i == 6) continue;
				if (i == 7) continue;
				if (i == 8) continue;
				if (i == 9) continue;
				if (i == 10) continue;
				if (i == 11) continue;
				if (mutateRect.choiceColor[i])
				{
					redRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
				else
				{
					greenRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
			}
		}
	}

	if (mutateQueensNest)
	{
		// ���콺 ����Ʈ�� ����׽�Ʈ �̹���
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateQueensNestImage->AlphaRender(hdc, _tileMap[i].left-30, _tileMap[i].top - 60, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// ��ġ ���� ���ο� ���� ���� �������ش�.
		for (int i = 0; i < BUILDINGTILEMAX; i++)
		{
			if (IntersectRect(&temp, &mutateRect.buildRect[i], &buildRectRender))
			{
				if (i == 3) continue;
				if (i == 7) continue;
				if (i == 8) continue;
				if (i == 9) continue;
				if (i == 10) continue;
				if (i == 11) continue;
				if (mutateRect.choiceColor[i])
				{
					redRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
				else
				{
					greenRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, ALPHA);
				}
			}
		}
	}

	//Rectangle(hdc, buildRectRender.left, buildRectRender.top, buildRectRender.right, buildRectRender.bottom);
}

void Drone::RenderUI(HDC hdc)
{	
	// ���� ��ġ ī�޶� �ݿ�
	SetCommandRect();
	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		//buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

		if (KEYMANAGER->IsToggleKey(VK_TAB))
		{
			for (int i = 0; i < COMMANDMAX; i++)
			{
				Rectangle(hdc, commandRect[i].left, commandRect[i].top, commandRect[i].right, commandRect[i].bottom);
			}
		}

		if (baseUIrender)
		{
			commandImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
			commandImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
			commandImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
			commandImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
			commandImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
			commandImage[SLOT8]->Render(hdc, commandRect[SLOT8].left, commandRect[SLOT8].top);
			commandImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);
		}
		if (baseBuildingUIrender)
		{
			baseBuildingImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
			baseBuildingImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
			baseBuildingImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
			baseBuildingImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top);
			baseBuildingImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
			baseBuildingImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
			baseBuildingImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);
		}
		if (highBuildingUIrender)
		{
			highBuildingImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
			highBuildingImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
			highBuildingImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
			highBuildingImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top);
			highBuildingImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
			highBuildingImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);
		}						
	}
}

void Drone::PlayAnimation()
{
	if (isTransHatchery)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 15)
			{
				baseBuildingSlot[SLOT1]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				baseBuildingSlot[SLOT1]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransHatchery = false;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransSpawningPool)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 15)
			{
				baseBuildingSlot[SLOT4]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				baseBuildingSlot[SLOT4]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransSpawningPool = false;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransHydraliskDen)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 15)
			{
				baseBuildingSlot[SLOT7]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				baseBuildingSlot[SLOT7]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransHydraliskDen = false;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransEvolutionChamber)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 15)
			{
				baseBuildingSlot[SLOT5]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				baseBuildingSlot[SLOT5]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransEvolutionChamber = false;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransCreepColony)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 10)
			{
				baseBuildingSlot[SLOT2]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				baseBuildingSlot[SLOT2]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransCreepColony = false;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransExtractor)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 13)
			{
				baseBuildingSlot[SLOT3]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				baseBuildingSlot[SLOT3]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransExtractor = false;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransSpire)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 15)
			{
				highBuildingSlot[SLOT1]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				highBuildingSlot[SLOT1]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransSpire = false;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransQueensNest)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 15)
			{
				highBuildingSlot[SLOT2]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				highBuildingSlot[SLOT2]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransQueensNest = false;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}

	else
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
}

bool Drone::CheckCollision()
{
	for (int i = 0; i < BUILDINGTILEMAX; i++)
	{
		if (mutateRect.choiceColor[i]) return false;
	}
	return true;
}

bool Drone::CheckMutate()
{
	if (isTransHatchery) return false;
	if (isTransSpawningPool) return false;
	if (isTransHydraliskDen) return false;
	if (isTransEvolutionChamber) return false;
	if (isTransCreepColony) return false;
	if (isTransExtractor) return false;
	if (isTransSpire) return false;
	if (isTransQueensNest) return false;
	
	return true;
}
