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
	//baseBuildingSlot[SLOT2] = IMAGEMANAGER->FindImage("CreepColonyUI");
	//baseBuildingSlot[SLOT3] = IMAGEMANAGER->FindImage("ExtractorUI");
	//baseBuildingSlot[SLOT4] = IMAGEMANAGER->FindImage("SpawningPoolUI");
	//baseBuildingSlot[SLOT5] = IMAGEMANAGER->FindImage("EvolutionChamberUI");
	//baseBuildingSlot[SLOT7] = IMAGEMANAGER->FindImage("HydraliskDenUI");
	//baseBuildingSlot[SLOT9] = IMAGEMANAGER->FindImage("Cancel");

	//highBuildingSlot[SLOT1] = IMAGEMANAGER->FindImage("SpireUI");
	//highBuildingSlot[SLOT2] = IMAGEMANAGER->FindImage("QueensNestUI");
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
			// 해처리
			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					mutateHatchery = true;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown('H'))
			{
				mutateHatchery = true;
			}

			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{

			}
			if (PtInRect(&commandRect[SLOT3], m_ptMouse))
			{

			}
			if (PtInRect(&commandRect[SLOT5], m_ptMouse))
			{

			}
			if (PtInRect(&commandRect[SLOT7], m_ptMouse))
			{

			}
			if (PtInRect(&commandRect[SLOT8], m_ptMouse))
			{

			}

			// 뒤로가기
			if (PtInRect(&commandRect[SLOT9], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					baseUIrender = true;
					baseBuildingUIrender = false;
					mutateHatchery = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
			{
				baseUIrender = true;
				baseBuildingUIrender = false;
				mutateHatchery = false;
			}
		}
		if (highBuildingUIrender)
		{
			if (PtInRect(&commandRect[SLOT9], m_ptMouse))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					baseUIrender = true;
					highBuildingUIrender = false;
				}
			}
			if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
			{
				baseUIrender = true;
				highBuildingUIrender = false;
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
			}
			// 설치가 불가할 때
			else
			{
				mutateHatchery = true;
				// 설치불가 메시지를 띄울지 결정
			}
		}
	}

	// 해처리 설치 장소에 도달했을 때 변태상태로 이미지를 바꿔준다.
	if (IntersectRect(&temp, &_tileMap[saveUnitPosition].rect, &unitStatus.unitRect))
	{
		isTransHatchery = true;
		unitStatus.unitImage = IMAGEMANAGER->FindImage("buildingBirthtest");
	}

	// 애니메이션의 프레임을 돌린다.
	PlayAnimation();

	// 변태상태가 아닐때 실행하는 부분.
	if (!isTransHatchery)
	{
		// A*실행
		UpdateAstar(unitStatus.unitRectX, unitStatus.unitRectY);

		// 변하는 각도에 따라 프레임을 바꿔준다.
		unitStatus.frameIndexY = ChangeImageFrame();

		// 길찾기를 통해 유닛을 이동한다.
		MoveUnit();

		// 유닛 렉트를 재설정해준다.
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
		unitStatus.unitImage->FrameRender(hdc, _tileMap[saveUnitPosition - 66].rect.left, _tileMap[saveUnitPosition - 66].rect.top, 
			unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImageWidthHalf,
			unitStatus.unitRectY - unitStatus.unitImageHeightHalf, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}

	if (mutateHatchery)
	{
		// 마우스 포인트에 해처리 이미지
		for (int i = 0; i < TILESIZE; i++)
		{
			if (PtInRect(&_tileMap[i].rect, m_ptMouse))
			{
				mutateHatcheryImage->Render(hdc, _tileMap[i].left, _tileMap[i].top);
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						mutateRect.buildRect[(j*4) + k] = RectMake(_tileMap[i].left + k * CELL_WIDTH, _tileMap[i].top + j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
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
					redRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, 100);
				}
				else
				{
					greenRectImage->AlphaRender(hdc, mutateRect.buildRect[i].left, mutateRect.buildRect[i].top, 100);
				}
			}
		}
	}

	//Rectangle(hdc, buildRectRender.left, buildRectRender.top, buildRectRender.right, buildRectRender.bottom);
}

void Drone::RenderUI(HDC hdc)
{	
	// 슬롯 위치 카메라 반영
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
