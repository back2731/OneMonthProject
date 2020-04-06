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
	unitStatus.unitCurrentHp = 40;
	unitStatus.unitAtk = 5;
	unitStatus.unitBaseAtk = 5;
	unitStatus.unitDef = 0;
	unitStatus.unitBaseDef = 0;
	unitStatus.unitTime = 0;
	unitStatus.unitSpeed = 5;

	unitStatus.unitMineralPrice = 50;
	unitStatus.unitGasPrice = 0;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("drone");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("2X2");
	unitStatus.unitWireFrame = IMAGEMANAGER->FindImage("droneWirefram");
	unitStatus.unitFrontProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressFront");
	unitStatus.unitBackProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressBack");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth() * 0.25, unitStatus.unitImage->GetFrameHeight() * 0.25);
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) * 0.5;;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) * 0.5;;
	unitStatus.unitPositionRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth() * 0.1, unitStatus.unitImage->GetFrameHeight() * 0.1);


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

	unitStatus.unitPortraitsImage = IMAGEMANAGER->FindImage("portraitsDrone");
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
	SetCommandSlot(SLOT5, new Gathering);
	SetCommandSlot(SLOT7, new BaseBuilding);
	SetCommandSlot(SLOT8, new HighBuilding);
	SetCommandSlot(SLOT9, new Burrow);
	
	// 명령 이미지 설정
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
	highBuildingSlot[SLOT4] = new BuildUltraliskCavern;
	highBuildingSlot[SLOT5] = new BuildDefilerMound;
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
	mutateUltraliskCavernImage = IMAGEMANAGER->FindImage("mutateUltraliskCavern");
	mutateDefilerMoundImage = IMAGEMANAGER->FindImage("mutateDefilerMound");

	abilityImage[SLOT1] = IMAGEMANAGER->FindImage("carapace");
	abilityImage[SLOT2] = IMAGEMANAGER->FindImage("spines");
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

	if (isClick && unitStatus.playerNumber == PLAYER1)
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

		if (baseUIrender)
		{
			// 기본 변태 슬롯으로 변경
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

			// 상위 변태 슬롯으로 변경
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
			baseBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("HatcheryUI");
			baseBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("CreepColonyUI");
			baseBuildingImage[SLOT3] = IMAGEMANAGER->FindImage("ExtractorUI");

			// 해처리
			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					baseBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("ClickHatchery");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 300)
					{
						mutateHatchery = true;

						mutateEvolutionChamber = false;
						mutateHydraliskDen = false;
						mutateSpawningPool = false;
						mutateCreepColony = false;
						mutateExtractor = false;
						baseBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("HatcheryUI");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('H'))
			{
				baseBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("ClickHatchery");
			}
			if (KEYMANAGER->IsOnceKeyUp('H'))
			{
				if (PLAYERMANAGER->GetMineral() >= 300)
				{
					mutateHatchery = true;

					mutateEvolutionChamber = false;
					mutateHydraliskDen = false;
					mutateSpawningPool = false;
					mutateCreepColony = false;
					mutateExtractor = false;
					baseBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("HatcheryUI");
				}
			}

			// 크립 콜로니
			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					baseBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("ClickCreepColony");
				}
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 75)
					{
						mutateCreepColony = true;

						mutateHatchery = false;
						mutateSpawningPool = false;
						mutateHydraliskDen = false;
						mutateEvolutionChamber = false;
						mutateExtractor = false;
						baseBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("CreepColonyUI");
					}
				}
			}				
			if (KEYMANAGER->IsStayKeyDown('C'))
			{
				baseBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("ClickCreepColony");
			}
			if (KEYMANAGER->IsOnceKeyDown('C'))
			{
				if (PLAYERMANAGER->GetMineral() >= 75)
				{
					mutateCreepColony = true;

					mutateHatchery = false;
					mutateSpawningPool = false;
					mutateHydraliskDen = false;
					mutateEvolutionChamber = false;
					mutateExtractor = false;
					baseBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("CreepColonyUI");
				}
			}

			// 익스트렉터
			if (PtInRect(&commandRect[SLOT3], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					baseBuildingImage[SLOT3] = IMAGEMANAGER->FindImage("ClickExtractor");
				}
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 50)
					{
						mutateExtractor = true;

						mutateHatchery = false;
						mutateSpawningPool = false;
						mutateHydraliskDen = false;
						mutateEvolutionChamber = false;
						mutateCreepColony = false;
						baseBuildingImage[SLOT3] = IMAGEMANAGER->FindImage("ExtractorUI");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('E'))
			{
				baseBuildingImage[SLOT3] = IMAGEMANAGER->FindImage("ClickExtractor");
			}
			if (KEYMANAGER->IsOnceKeyDown('E'))
			{
				if (PLAYERMANAGER->GetMineral() >= 50)
				{
					mutateExtractor = true;

					mutateHatchery = false;
					mutateSpawningPool = false;
					mutateHydraliskDen = false;
					mutateEvolutionChamber = false;
					mutateCreepColony = false;
					baseBuildingImage[SLOT3] = IMAGEMANAGER->FindImage("ExtractorUI");
				}
			}
			
			// 스포닝풀
			if (BUILDMANAGER->GetHaveHatchery())
			{
				baseBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("SpawningPoolUI");

				if (PtInRect(&commandRect[SLOT4], m_ptMouse))
				{
					if(KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
					{ 
						baseBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("ClickSpawningPool");
					}
					if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
					{
						if (PLAYERMANAGER->GetMineral() >= 200)
						{
							mutateSpawningPool = true;

							mutateHatchery = false;
							mutateEvolutionChamber = false;
							mutateHydraliskDen = false;
							mutateCreepColony = false;
							mutateExtractor = false;
							baseBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("SpawningPoolUI");
						}
					}
				}
				if (KEYMANAGER->IsStayKeyDown('S'))
				{
					baseBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("ClickSpawningPool");
				}
				if (KEYMANAGER->IsOnceKeyUp('S'))
				{
					if (PLAYERMANAGER->GetMineral() >= 200)
					{
						mutateSpawningPool = true;

						mutateHatchery = false;
						mutateEvolutionChamber = false;
						mutateHydraliskDen = false;
						mutateCreepColony = false;
						mutateExtractor = false;
						baseBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("SpawningPoolUI");
					}
				}
			}
			else
			{
				baseBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("DisabledSpawningPool");				
			}
			
			// 에볼루션챔버
			if (BUILDMANAGER->GetHaveHatchery())
			{
				baseBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("EvolutionChamberUI");

				if (PtInRect(&commandRect[SLOT5], m_ptMouse))
				{
					if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
					{
						baseBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("ClickEvolutionChamber");
					}
					if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
					{
						if (PLAYERMANAGER->GetMineral() >= 75)
						{
							mutateEvolutionChamber = true;

							mutateHatchery = false;
							mutateSpawningPool = false;
							mutateHydraliskDen = false;
							mutateCreepColony = false;
							mutateExtractor = false;
							baseBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("EvolutionChamberUI");
						}
					}
				}
				if (KEYMANAGER->IsStayKeyDown('V'))
				{
					baseBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("ClickEvolutionChamber");
				}
				if (KEYMANAGER->IsOnceKeyUp('V'))
				{
					if (PLAYERMANAGER->GetMineral() >= 75)
					{
						mutateEvolutionChamber = true;

						mutateHatchery = false;
						mutateSpawningPool = false;
						mutateHydraliskDen = false;
						mutateCreepColony = false;
						mutateExtractor = false;
						baseBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("EvolutionChamberUI");
					}
				}
			}
			else
			{
				baseBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("DisabledEvolutionChamber");
			}

			// 히드라리스크덴
			if (BUILDMANAGER->GetHaveSpawningpool())
			{
				baseBuildingImage[SLOT7] = IMAGEMANAGER->FindImage("HydraliskDenUI");

				if (PtInRect(&commandRect[SLOT7], m_ptMouse))
				{
					if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
					{
						baseBuildingImage[SLOT7] = IMAGEMANAGER->FindImage("ClickHydraliskDen");
					}
					if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
					{
						if (PLAYERMANAGER->GetMineral() >= 100 && PLAYERMANAGER->GetVespeneGas() >= 50)
						{
							mutateHydraliskDen = true;

							mutateHatchery = false;
							mutateSpawningPool = false;
							mutateEvolutionChamber = false;
							mutateCreepColony = false;
							mutateExtractor = false;
						}
					}
					if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
					{
						baseBuildingImage[SLOT7] = IMAGEMANAGER->FindImage("HydraliskDenUI");
					}
				}
				if (KEYMANAGER->IsStayKeyDown('D'))
				{
					baseBuildingImage[SLOT7] = IMAGEMANAGER->FindImage("ClickHydraliskDen");
				}
				if (KEYMANAGER->IsOnceKeyDown('D'))
				{
					if (PLAYERMANAGER->GetMineral() >= 100 && PLAYERMANAGER->GetVespeneGas() >= 50)
					{
						mutateHydraliskDen = true;

						mutateHatchery = false;
						mutateSpawningPool = false;
						mutateEvolutionChamber = false;
						mutateCreepColony = false;
						mutateExtractor = false;
					}
				}					
				if (KEYMANAGER->IsOnceKeyUp('D'))
				{
					baseBuildingImage[SLOT7] = IMAGEMANAGER->FindImage("HydraliskDenUI");
				}
			}
			else
			{
				baseBuildingImage[SLOT7] = IMAGEMANAGER->FindImage("DisabledHydraliskDen");
			}
			
			// 뒤로가기
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
			// 스파이어
			if (BUILDMANAGER->GetHaveLair())
			{
				highBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("SpireUI");
				highBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("QueensNestUI");

				if (PtInRect(&commandRect[SLOT1], m_ptMouse))
				{
					if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
					{
						highBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("ClickSpire");
					}
					if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
					{
						if (PLAYERMANAGER->GetMineral() >= 200 && PLAYERMANAGER->GetVespeneGas() >= 150)
						{
							mutateSpire = true;

							mutateQueensNest = false;
							mutateUltraliskCavern = false;
							mutateDefilerMound = false;
							highBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("SpireUI");
						}
					}
				}
				if (KEYMANAGER->IsStayKeyDown('S'))
				{
					highBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("ClickSpire");
				}
				if (KEYMANAGER->IsOnceKeyDown('S'))
				{
					if (PLAYERMANAGER->GetMineral() >= 200 && PLAYERMANAGER->GetVespeneGas() >= 150)
					{
						mutateSpire = true;

						mutateQueensNest = false;
						mutateUltraliskCavern = false;
						mutateDefilerMound = false;
						highBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("SpireUI");
					}
				}					

				// 퀸즈네스트
				if (PtInRect(&commandRect[SLOT2], m_ptMouse))
				{
					if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
					{
						highBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("ClickQueensNest");
					}
					if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
					{
						if (PLAYERMANAGER->GetMineral() >= 150 && PLAYERMANAGER->GetVespeneGas() >= 100)
						{
							mutateQueensNest = true;

							mutateSpire = false;
							mutateUltraliskCavern = false;
							mutateDefilerMound = false;
							highBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("QueensNestUI");
						}

					}
				}
				if (KEYMANAGER->IsStayKeyDown('Q'))
				{
					highBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("ClickQueensNest");
				}
				if (KEYMANAGER->IsOnceKeyDown('Q'))
				{
					if (PLAYERMANAGER->GetMineral() >= 150 && PLAYERMANAGER->GetVespeneGas() >= 100)
					{
						mutateQueensNest = true;

						mutateSpire = false;
						mutateUltraliskCavern = false;
						mutateDefilerMound = false;
						highBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("QueensNestUI");
					}
				}
			}
			else
			{
				highBuildingImage[SLOT1] = IMAGEMANAGER->FindImage("DisabledSpire");
				highBuildingImage[SLOT2] = IMAGEMANAGER->FindImage("DisabledQueensNest");
			}

			// 울트라리스크 캐번
			if (BUILDMANAGER->GetHaveHive())
			{
				highBuildingImage[SLOT3] = IMAGEMANAGER->FindImage("NydusCanalUI");
				highBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("UltraliskCavernUI");
				highBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("DefilerMoundUI");

				if (PtInRect(&commandRect[SLOT4], m_ptMouse))
				{
					if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
					{
						highBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("ClickUltraliskCavern");
					}
					if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
					{
						if (PLAYERMANAGER->GetMineral() >= 150 && PLAYERMANAGER->GetVespeneGas() >= 200)
						{
							mutateUltraliskCavern = true;

							mutateSpire = false;
							mutateQueensNest = false;
							mutateDefilerMound = false;
							highBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("UltraliskCavernUI");
						}
					}
				}					
				if (KEYMANAGER->IsStayKeyDown('U'))
				{
					highBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("ClickUltraliskCavern");
				}
				if (KEYMANAGER->IsOnceKeyDown('U'))
				{
					if (PLAYERMANAGER->GetMineral() >= 150 && PLAYERMANAGER->GetVespeneGas() >= 200)
					{
						mutateUltraliskCavern = true;

						mutateSpire = false;
						mutateQueensNest = false;
						mutateDefilerMound = false;
						highBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("UltraliskCavernUI");
					}
				}

				// 디파일러 마운드
				if (PtInRect(&commandRect[SLOT5], m_ptMouse))
				{
					if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
					{
						highBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("ClickDefilerMound");
					}
					if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
					{
						if (PLAYERMANAGER->GetMineral() >= 100 && PLAYERMANAGER->GetVespeneGas() >= 100)
						{
							mutateDefilerMound = true;

							mutateSpire = false;
							mutateQueensNest = false;
							mutateUltraliskCavern = false;
						}
					}
					if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
					{
						highBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("DefilerMoundUI");
					}
				}
				if (KEYMANAGER->IsStayKeyDown('D'))
				{
					highBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("ClickDefilerMound");
				}
				if (KEYMANAGER->IsOnceKeyDown('D'))
				{
					if (PLAYERMANAGER->GetMineral() >= 100 && PLAYERMANAGER->GetVespeneGas() >= 100)
					{
						mutateDefilerMound = true;

						mutateSpire = false;
						mutateQueensNest = false;
						mutateUltraliskCavern = false;
						highBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("DefilerMoundUI");
					}
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					highBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("DefilerMoundUI");
				}
			}
			else
			{
				highBuildingImage[SLOT3] = IMAGEMANAGER->FindImage("DisabledNydusCanal");
				highBuildingImage[SLOT4] = IMAGEMANAGER->FindImage("DisabledUltraliskCavern");
				highBuildingImage[SLOT5] = IMAGEMANAGER->FindImage("DisabledDefilerMound");
			}

			if (PtInRect(&commandRect[SLOT9], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					baseUIrender = true;
					highBuildingUIrender = false;

					mutateSpire = false;
					mutateQueensNest = false;
					mutateUltraliskCavern = false;
					mutateDefilerMound = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
			{
				baseUIrender = true;
				highBuildingUIrender = false;
				
				mutateSpire = false;
				mutateQueensNest = false;
				mutateUltraliskCavern = false;
				mutateDefilerMound = false;
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
		mutateUltraliskCavern = false;

		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
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
			// 설치가 불가할 때
			else
			{
				mutateHatchery = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}
	else if (mutateSpawningPool)
	{
		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
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
			// 설치가 불가할 때
			else
			{
				mutateSpawningPool = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}
	else if (mutateHydraliskDen)
	{
		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
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
			// 설치가 불가할 때
			else
			{
				mutateHydraliskDen = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}
	else if (mutateEvolutionChamber)
	{
		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
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
			// 설치가 불가할 때
			else
			{
				mutateEvolutionChamber = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}
	else if (mutateCreepColony)
	{
		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
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
			// 설치가 불가할 때
			else
			{
				mutateCreepColony = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}
	else if (mutateExtractor)
	{
		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
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
			// 설치가 불가할 때
			else
			{
				mutateExtractor = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}
	else if (mutateSpire)
	{
		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
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
			// 설치가 불가할 때
			else
			{
				mutateSpire = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}
	else if (mutateQueensNest)
	{
		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
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
			// 설치가 불가할 때
			else
			{
				mutateQueensNest = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}
	else if (mutateUltraliskCavern)
	{
		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateUltraliskCavern = false;
				highBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveUltraliskCavern = true;
			}
			// 설치가 불가할 때
			else
			{
				mutateUltraliskCavern = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}
	else if (mutateDefilerMound)
	{
		// 해당 장소가 설치 가능한 장소인지를 타일의 Block값으로 판별해 저장해둔다.
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

		// 설치모드 상태에서의 명령문
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			// 설치가 가능할 때
			if (CheckCollision())
			{
				SetEndTile(TILEX + 1);
				SetAstarVector();
				SetStartTile();

				// 설치하는 해당 위치를 저장해준다.
				for (int i = 0; i < TILESIZE; i++)
				{
					if (PtInRect(&_tileMap[i].rect, m_ptMouse))
					{
						saveUnitPosition = i + TILEX + 1;
					}
				}

				mutateDefilerMound = false;
				highBuildingUIrender = false;
				baseUIrender = false;
				isClick = false;
				isArriveDefilerMound = true;
			}
			// 설치가 불가할 때
			else
			{
				mutateDefilerMound = true;
				isClick = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}

	// 설치 장소에 도달했을 때 변태상태로 이미지를 바꿔준다.
	if (IntersectRect(&temp, &_tileMap[saveUnitPosition].rect, &unitStatus.unitRect))
	{
		if (isArriveHatchery)
		{
			isTransHatchery = true;
			isArriveHatchery = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		else if (isArriveSpawningPool)
		{
			isTransSpawningPool = true;
			isArriveSpawningPool = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		else if (isArriveHydraliskDen)
		{
			isTransHydraliskDen = true;
			isArriveHydraliskDen = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		else if (isArriveEvolutionChamber)
		{
			isTransEvolutionChamber = true;
			isArriveEvolutionChamber = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		else if (isArriveCreepColony)
		{
			isTransCreepColony = true;
			isArriveCreepColony = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthSmall");
		}
		else if (isArriveExtractor)
		{
			isTransExtractor = true;
			isArriveExtractor = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthBig");
		}
		else if (isArriveSpire)
		{
			isTransSpire = true;
			isArriveSpire = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		else if (isArriveQueensNest)
		{
			isTransQueensNest = true;
			isArriveQueensNest = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		else if (isArriveUltraliskCavern)
		{
			isTransUltraliskCavern = true;
			isArriveUltraliskCavern = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}
		else if (isArriveDefilerMound)
		{
			isTransDefilerMound = true;
			isArriveDefilerMound = false;
			unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthMiddle");
		}

	}

	// 애니메이션의 프레임을 돌린다.
	PlayAnimation();
	PlayPortraits();

	// 변태상태가 아닐때 실행하는 부분.
	if (CheckMutate())
	{
		// A*실행
		UpdateAstar(unitStatus.unitRectX, unitStatus.unitRectY);

		// 변하는 각도에 따라 프레임을 바꿔준다.
		unitStatus.frameIndexY = ChangeImageFrame();

		// 길찾기를 통해 유닛을 이동한다.
		MoveUnit(unitStatus.unitSpeed);

		// 유닛 렉트를 재설정해준다.
		unitStatus.unitRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, unitStatus.unitImageWidthQuarter, unitStatus.unitImageHeightQuarter);
	}

	buildRectRender = RectMake(m_ptMouse.x, m_ptMouse.y, CELL_WIDTH * 4, CELL_HEIGHT * 3);

	unitStatus.unitDef = 0 + UPGRADEMANAGER->GetEvolveCarapace();

	unitStatus.unitPositionRect = RectMakeCenter(unitStatus.unitRectX, unitStatus.unitRectY, 2, 2);

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
	else if (isTransUltraliskCavern)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX * 2].rect.left, _tileMap[saveUnitPosition - 2].rect.top - 30,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransDefilerMound)
	{
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - TILEX].rect.left - 30, _tileMap[saveUnitPosition - 2].rect.top - 30,
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImageWidthHalf,
			unitStatus.unitRectY - unitStatus.unitImageHeightHalf, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}

	//Rectangle(hdc, buildRectRender.left, buildRectRender.top, buildRectRender.right, buildRectRender.bottom);
}

void Drone::RenderUI(HDC hdc)
{	
	// 슬롯 위치 카메라 반영
	SetCommandRect();
	SetAbilityRect();

	unitStatus.unitPortraitsImage->FrameRender(hdc, CAMERAMANAGER->GetCameraCenter().x + 170,	CAMERAMANAGER->GetCameraCenter().y + 310, unitStatus.unitPortraitsFrameX, unitStatus.unitPortraitsFrameY);

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

		if (baseUIrender)
		{
			commandImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
			commandImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
			commandImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
			commandImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
			commandImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
			commandImage[SLOT8]->Render(hdc, commandRect[SLOT8].left, commandRect[SLOT8].top);
			commandImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);

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
			if (PtInRect(&commandRect[SLOT5], m_ptMouse))
			{
				descriptionImage[SLOT5] = IMAGEMANAGER->FindImage("GatherUI");
				descriptionImage[SLOT5]->Render(hdc, commandRect[SLOT5].left - descriptionImage[SLOT5]->GetWidth() / 2, commandRect[SLOT5].top - descriptionImage[SLOT5]->GetHeight());
			}
			if (PtInRect(&commandRect[SLOT7], m_ptMouse))
			{
				descriptionImage[SLOT7] = IMAGEMANAGER->FindImage("BasicMutationUI");
				descriptionImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top - descriptionImage[SLOT7]->GetHeight());
			}
			if (PtInRect(&commandRect[SLOT8], m_ptMouse))
			{
				descriptionImage[SLOT8] = IMAGEMANAGER->FindImage("advancedMutationUI");
				descriptionImage[SLOT8]->Render(hdc, commandRect[SLOT8].left - descriptionImage[SLOT8]->GetWidth() / 2, commandRect[SLOT8].top - descriptionImage[SLOT8]->GetHeight());
			}
			if (PtInRect(&commandRect[SLOT9], m_ptMouse))
			{
				descriptionImage[SLOT9] = IMAGEMANAGER->FindImage("burrowUI");
				descriptionImage[SLOT9]->Render(hdc, commandRect[SLOT9].left - descriptionImage[SLOT9]->GetWidth() + 50, commandRect[SLOT9].top - descriptionImage[SLOT9]->GetHeight());
			}
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

			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				descriptionImage[SLOT1] = IMAGEMANAGER->FindImage("mutateIntoHatchery");
				descriptionImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].bottom);
			}
			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{	
				descriptionImage[SLOT2] = IMAGEMANAGER->FindImage("mutateIntoCreepColony");
				descriptionImage[SLOT2]->Render(hdc, commandRect[SLOT2].left - descriptionImage[SLOT2]->GetWidth() / 2, commandRect[SLOT2].bottom);
			}
			if (PtInRect(&commandRect[SLOT3], m_ptMouse))
			{
				descriptionImage[SLOT3] = IMAGEMANAGER->FindImage("mutateIntoExtractor");
				descriptionImage[SLOT3]->Render(hdc, commandRect[SLOT3].left - descriptionImage[SLOT3]->GetWidth() + 50, commandRect[SLOT3].bottom);
			}
			if (PtInRect(&commandRect[SLOT4], m_ptMouse))
			{
				descriptionImage[SLOT4] = IMAGEMANAGER->FindImage("mutateIntoSpawningPool");
				descriptionImage[SLOT4]->Render(hdc, commandRect[SLOT4].left - 50, commandRect[SLOT4].top - descriptionImage[SLOT4]->GetHeight());
			}
			if (PtInRect(&commandRect[SLOT5], m_ptMouse))
			{
				descriptionImage[SLOT5] = IMAGEMANAGER->FindImage("mutateIntoEvolutionChamber");
				descriptionImage[SLOT5]->Render(hdc, commandRect[SLOT5].left - descriptionImage[SLOT5]->GetWidth() / 2, commandRect[SLOT5].top - descriptionImage[SLOT5]->GetHeight());
			}
			if (PtInRect(&commandRect[SLOT7], m_ptMouse))
			{
				if (BUILDMANAGER->GetHaveSpawningpool())
				{
					descriptionImage[SLOT7] = IMAGEMANAGER->FindImage("mutateIntoHydraliskDen");
					descriptionImage[SLOT7]->Render(hdc, commandRect[SLOT7].left - 50, commandRect[SLOT7].top - descriptionImage[SLOT7]->GetHeight());
				}
				else
				{
					descriptionImage[SLOT7] = IMAGEMANAGER->FindImage("hydraliskDenRequires");
					descriptionImage[SLOT7]->Render(hdc, commandRect[SLOT7].left - 50, commandRect[SLOT7].top - descriptionImage[SLOT7]->GetHeight());
				}
			}
			if (PtInRect(&commandRect[SLOT9], m_ptMouse))
			{
				descriptionImage[SLOT9] = IMAGEMANAGER->FindImage("ESCcancelUI");
				descriptionImage[SLOT9]->Render(hdc, commandRect[SLOT9].left - descriptionImage[SLOT9]->GetWidth() + 50, commandRect[SLOT9].top - descriptionImage[SLOT9]->GetHeight());
			}
		}
		if (highBuildingUIrender)
		{
			highBuildingImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
			highBuildingImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
			highBuildingImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
			highBuildingImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top);
			highBuildingImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
			highBuildingImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);

			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				if (BUILDMANAGER->GetHaveLair())
				{
					descriptionImage[SLOT1] = IMAGEMANAGER->FindImage("mutateIntoSpire");
					descriptionImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].bottom);
				}
				else
				{
					descriptionImage[SLOT1] = IMAGEMANAGER->FindImage("spireRequires");
					descriptionImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].bottom);
				}
			}
			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{
				if (BUILDMANAGER->GetHaveLair())
				{
					descriptionImage[SLOT2] = IMAGEMANAGER->FindImage("mutateIntoQueensNest");
					descriptionImage[SLOT2]->Render(hdc, commandRect[SLOT2].left - descriptionImage[SLOT2]->GetWidth() / 2, commandRect[SLOT2].bottom);
				}
				else
				{
					descriptionImage[SLOT2] = IMAGEMANAGER->FindImage("queensNestRequires");
					descriptionImage[SLOT2]->Render(hdc, commandRect[SLOT2].left - descriptionImage[SLOT2]->GetWidth() / 2, commandRect[SLOT2].bottom);
				}
			}
			if (PtInRect(&commandRect[SLOT3], m_ptMouse))
			{
				if (BUILDMANAGER->GetHaveHive())
				{
					descriptionImage[SLOT3] = IMAGEMANAGER->FindImage("mutateIntoNydusCanal");
					descriptionImage[SLOT3]->Render(hdc, commandRect[SLOT3].left - descriptionImage[SLOT3]->GetWidth() + 50, commandRect[SLOT3].bottom);
				}
				else
				{
					descriptionImage[SLOT3] = IMAGEMANAGER->FindImage("nydusCanalRequires");
					descriptionImage[SLOT3]->Render(hdc, commandRect[SLOT3].left - descriptionImage[SLOT3]->GetWidth() + 50, commandRect[SLOT3].bottom);
				}
			}
			if (PtInRect(&commandRect[SLOT4], m_ptMouse))
			{
				if (BUILDMANAGER->GetHaveHive())
				{
					descriptionImage[SLOT4] = IMAGEMANAGER->FindImage("mutateIntoUltraliskCavern");
					descriptionImage[SLOT4]->Render(hdc, commandRect[SLOT4].left - 50, commandRect[SLOT4].top - descriptionImage[SLOT4]->GetHeight());
				}
				else
				{
					descriptionImage[SLOT4] = IMAGEMANAGER->FindImage("ultraliskCavernRequires");
					descriptionImage[SLOT4]->Render(hdc, commandRect[SLOT4].left - 50, commandRect[SLOT4].top - descriptionImage[SLOT4]->GetHeight());
				}
			}
			if (PtInRect(&commandRect[SLOT5], m_ptMouse))
			{
				if (BUILDMANAGER->GetHaveHive())
				{
					descriptionImage[SLOT5] = IMAGEMANAGER->FindImage("mutateIntoDefilerMound");
					descriptionImage[SLOT5]->Render(hdc, commandRect[SLOT5].left - descriptionImage[SLOT5]->GetWidth() / 2, commandRect[SLOT5].top - descriptionImage[SLOT5]->GetHeight());
				}
				else
				{
					descriptionImage[SLOT5] = IMAGEMANAGER->FindImage("defilerMoundRequires");
					descriptionImage[SLOT5]->Render(hdc, commandRect[SLOT5].left - descriptionImage[SLOT5]->GetWidth() / 2, commandRect[SLOT5].top - descriptionImage[SLOT5]->GetHeight());
				}
			}
			if (PtInRect(&commandRect[SLOT9], m_ptMouse))
			{
				descriptionImage[SLOT9] = IMAGEMANAGER->FindImage("ESCcancelUI");
				descriptionImage[SLOT9]->Render(hdc, commandRect[SLOT9].left - descriptionImage[SLOT9]->GetWidth() + 50, commandRect[SLOT9].top - descriptionImage[SLOT9]->GetHeight());
			}
		}				
		
		// 능력치 이미지 렌더
		abilityImage[SLOT1]->Render(hdc, abilityRect[SLOT1].left, abilityRect[SLOT1].top);
		abilityImage[SLOT2]->Render(hdc, abilityRect[SLOT2].left, abilityRect[SLOT2].top);

		SetTextColor(hdc, RGB(0, 222, 0));
		sprintf_s(str, "%d", unitStatus.unitCurrentHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 240, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		sprintf_s(str, "/   %d", unitStatus.unitMaxHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 200, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));

		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(str, "Zerg Drone");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 80, CAMERAMANAGER->GetCameraCenter().y + 290, str, strlen(str));


		sprintf_s(str, "kills : 0");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 60, CAMERAMANAGER->GetCameraCenter().y + 340, str, strlen(str));

		// 능력치 업그레이드 단계 렌더
		sprintf_s(str, "%d", UPGRADEMANAGER->GetEvolveCarapace());
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 60, CAMERAMANAGER->GetCameraCenter().y + 419, str, strlen(str));

		sprintf_s(str, "0");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x + 10, CAMERAMANAGER->GetCameraCenter().y + 419, str, strlen(str));

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
		if (PtInRect(&abilityRect[SLOT2], m_ptMouse))
		{
			abilityDescriptionImage[SLOT2] = IMAGEMANAGER->FindImage("spinesUI");
			abilityDescriptionImage[SLOT2]->Render(hdc, abilityRect[SLOT2].right, abilityRect[SLOT2].top);

			sprintf_s(str, "%d", unitStatus.unitBaseAtk);
			TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x + 129, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		}

		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}


	if (mutateHatchery)
	{
		// 마우스 포인트에 해처리 이미지
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateHatcheryImage->AlphaRender(hdc, _tileMap[i].left, _tileMap[i].top, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (mutateSpawningPool)
	{
		// 마우스 포인트에 스포닝풀 이미지
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

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (mutateHydraliskDen)
	{
		// 마우스 포인트에 히드라리스크덴 이미지
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

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (mutateEvolutionChamber)
	{
		// 마우스 포인트에 에볼루션 챔버 이미지
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

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (mutateCreepColony)
	{
		// 마우스 포인트에 크립 콜로니 이미지
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

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (mutateExtractor)
	{
		// 마우스 포인트에 익스트렉터 이미지
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

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (mutateSpire)
	{
		// 마우스 포인트에 스파이어 이미지
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

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (mutateQueensNest)
	{
		// 마우스 포인트에 퀸즈네스트 이미지
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateQueensNestImage->AlphaRender(hdc, _tileMap[i].left - 30, _tileMap[i].top - 60, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (mutateUltraliskCavern)
	{
		// 마우스 포인트에 울트라리스크 캐번 이미지
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateUltraliskCavernImage->AlphaRender(hdc, _tileMap[i].left - 30, _tileMap[i].top - 60, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (mutateDefilerMound)
	{
		// 마우스 포인트에 울트라리스크 캐번 이미지
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateDefilerMoundImage->AlphaRender(hdc, _tileMap[i].left, _tileMap[i].top - 64, ALPHA);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j * 4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
					}
				}
			}
		}

		// 설치 가능 여부에 따라 색을 렌더해준다.
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
	else if (isTransUltraliskCavern)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 15)
			{
				highBuildingSlot[SLOT4]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				highBuildingSlot[SLOT4]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransUltraliskCavern = false;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransDefilerMound)
		{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX == 15)
			{
				highBuildingSlot[SLOT5]->GetBirthXY(_tileMap[saveUnitPosition - TILEX - 1].rect.left, _tileMap[saveUnitPosition - TILEX - 1].rect.top);
				highBuildingSlot[SLOT5]->Update();
			}
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransDefilerMound = false;
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
	if (isTransUltraliskCavern) return false;
	if (isTransDefilerMound) return false;
	
	return true;
}
