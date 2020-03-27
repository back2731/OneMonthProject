#include "stdafx.h"
#include "Larva.h"


Larva::Larva()
{
}


Larva::~Larva()
{
}

Larva::Larva(int _playerNumber, POINT birthXY, int _hatcheryX, int _hatcheryY, int _larvaNumber)
{
	progressBar = new ProgressBar;
	unitStatus.unitKind = LARVA;

	hatcheryX = _hatcheryX;
	hatcheryY = _hatcheryY;
	larvaNumber = _larvaNumber;

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 25;
	unitStatus.unitCurrentHp = 8 + RND->GetInt(17);
	unitStatus.unitAtk = 0;
	unitStatus.unitDef = 10;
	unitStatus.unitTime = 0;

	unitStatus.unitMineralPrice = 0;
	unitStatus.unitGasPrice = 0;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("larva");
	unitStatus.enemyUnitImage1 = IMAGEMANAGER->FindImage("enemyLarva");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("1X1");
	unitStatus.unitFrontProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressFront");
	unitStatus.unitBackProgressImage = IMAGEMANAGER->FindImage("ZergUnitProgressBack");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth(), unitStatus.unitImage->GetFrameHeight());
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) / 2;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) / 2;
	
	unitStatus.unitImageWidthHalf = unitStatus.unitImage->GetFrameWidth() * 0.5;
	unitStatus.unitImageHeightHalf = unitStatus.unitImage->GetFrameHeight() * 0.5;
	unitStatus.unitImageWidthQuarter = unitStatus.unitImage->GetFrameWidth() * 0.25;
	unitStatus.unitImageHeightQuarter = unitStatus.unitImage->GetFrameHeight() * 0.25;

	unitStatus.unitSelectImageWidth = unitStatus.unitSelectImage->GetWidth() * 0.5;
	unitStatus.unitSelectImageHeight = unitStatus.unitSelectImage->GetHeight() * 0.5;

	unitStatus.unitProgressWidth = unitStatus.unitBackProgressImage->GetWidth() * 0.5;
	unitStatus.unitProgressHeight = unitStatus.unitBackProgressImage->GetHeight() * 0.5;


	unitStatus.frameCount = 0;
	unitStatus.frameIndexY = RND->GetInt(16);

	isClick = false;
	isTransform = false;

	isTransDrone = false;
	isTransZergling = false;

	//direction = RIGHTDOWN;

	progressBar->Init("images/UI/ZergUnitProgressFront.bmp", "images/UI/ZergUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);

	// 명령 슬롯 생성
	SetCommandSlot(SLOT1, new TransformDrone);
	SetCommandSlot(SLOT2, new TransformZergling);
	SetCommandSlot(SLOT3, new TransformOverlord);
	SetCommandSlot(SLOT4, new TransformHydralisk);
	SetCommandSlot(SLOT5, new TransformMutalisk);
	SetCommandSlot(SLOT6, new TransformScourge);
	SetCommandSlot(SLOT7, new TransformQueen);
	SetCommandSlot(SLOT8, new TransformUltralisk);
	SetCommandSlot(SLOT9, new TransformDefiler);

	// 명령 이미지 설정
	commandImage[SLOT1] = IMAGEMANAGER->FindImage("TransformDrone");
	commandImage[SLOT2] = IMAGEMANAGER->FindImage("TransformZergling");
	commandImage[SLOT3] = IMAGEMANAGER->FindImage("TransformOverlord");
	commandImage[SLOT4] = IMAGEMANAGER->FindImage("TransformHydralisk");
	commandImage[SLOT5] = IMAGEMANAGER->FindImage("TransformMutalisk");
	commandImage[SLOT6] = IMAGEMANAGER->FindImage("TransformScourge");
	commandImage[SLOT7] = IMAGEMANAGER->FindImage("TransformQueen");
	commandImage[SLOT8] = IMAGEMANAGER->FindImage("TransformUltralisk");
	commandImage[SLOT9] = IMAGEMANAGER->FindImage("TransformDefiler");

	SetCommandRect();
}

HRESULT Larva::Init()
{
	return S_OK;
}

void Larva::Release()
{
	SAFE_DELETE(progressBar);
}

void Larva::Update()
{
	progressBar->SetGauge(unitStatus.unitCurrentHp, unitStatus.unitMaxHp);

	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		// 드론 생산
		if (PtInRect(&commandRect[SLOT1], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransDrone(true);
			}

		}
		if (KEYMANAGER->IsOnceKeyDown('D'))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			UNITMANAGER->SetInputCommandTransDrone(true);
		}
		if (UNITMANAGER->GetInputCommandTransDrone())
		{
			isClick = false;

			isTransDrone = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("droneBirth");
		}

		// 저글링 생산
		if (PtInRect(&commandRect[SLOT2], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransZergling(true);
			}

		}
		if (KEYMANAGER->IsOnceKeyDown('Z'))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			UNITMANAGER->SetInputCommandTransZergling(true);
		}
		if (UNITMANAGER->GetInputCommandTransZergling())
		{
			isClick = false;

			isTransZergling = true;
			
			unitStatus.unitImage = IMAGEMANAGER->FindImage("zerglingBirth");
		}

		// 오버로드 생산
		if (PtInRect(&commandRect[SLOT3], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransOverlord(true);
			}

		}
		if (KEYMANAGER->IsOnceKeyDown('O'))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			UNITMANAGER->SetInputCommandTransOverlord(true);
		}
		if (UNITMANAGER->GetInputCommandTransOverlord())
		{
			isClick = false;

			isTransOverlord = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("overlordBirth");
		}

		// 히드라 생산
		if (PtInRect(&commandRect[SLOT4], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransHydralisk(true);
			}

		}
		if (KEYMANAGER->IsOnceKeyDown('H'))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			UNITMANAGER->SetInputCommandTransHydralisk(true);
		}
		if (UNITMANAGER->GetInputCommandTransHydralisk())
		{
			isClick = false;

			isTransHydralisk = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("hydraBirth");
		}

		// 뮤탈리스크 생산
		if (PtInRect(&commandRect[SLOT5], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransMutalisk(true);
			}

		}
		if (KEYMANAGER->IsOnceKeyDown('M'))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			UNITMANAGER->SetInputCommandTransMutalisk(true);
		}
		if (UNITMANAGER->GetInputCommandTransMutalisk())
		{
			isClick = false;

			isTransMutalisk = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("mutaliskBirth");
		}

		// 스커지 생산
		if (PtInRect(&commandRect[SLOT6], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransScourge(true);
			}

		}
		if (KEYMANAGER->IsOnceKeyDown('S'))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			UNITMANAGER->SetInputCommandTransScourge(true);
		}
		if (UNITMANAGER->GetInputCommandTransScourge())
		{
			isClick = false;

			isTransScourge = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("scourgeBirth");
		}
		
		// 스커지 생산
		if (PtInRect(&commandRect[SLOT7], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransQueen(true);
			}
		}
		if (KEYMANAGER->IsOnceKeyDown('Q'))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			UNITMANAGER->SetInputCommandTransQueen(true);
		}
		if (UNITMANAGER->GetInputCommandTransQueen())
		{
			isClick = false;

			isTransQueen = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("queenBirth");
		}
		
		// 울트라리스크 생산
		if (PtInRect(&commandRect[SLOT8], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransUltralisk(true);
			}
		}
		if (KEYMANAGER->IsOnceKeyDown('U'))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			UNITMANAGER->SetInputCommandTransUltralisk(true);
		}
		if (UNITMANAGER->GetInputCommandTransUltralisk())
		{
			isClick = false;

			isTransUltralisk = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("ultraBirth");
		}

		// 디파일러 생산
		if (PtInRect(&commandRect[SLOT9], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransDefiler(true);
			}
		}
		if (KEYMANAGER->IsOnceKeyDown('F'))
		{
			// 눌렸다는 명령을 true 해주는 것을 만든다.
			UNITMANAGER->SetInputCommandTransDefiler(true);
		}
		if (UNITMANAGER->GetInputCommandTransDefiler())
		{
			isClick = false;

			isTransDefiler = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("defilerBirth");
		}
	}

	PlayAnimation();
}

void Larva::Render(HDC hdc)
{
	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		unitStatus.unitSelectImage->Render(hdc, unitStatus.unitRectX - unitStatus.unitSelectImageWidth, unitStatus.unitRectY - unitStatus.unitSelectImageHeight);
		progressBar->Render(hdc, unitStatus.unitRectX - unitStatus.unitProgressWidth, unitStatus.unitRectY + 20);
	}
	if (isTransDrone)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left-60, unitStatus.unitRect.top-50, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransZergling)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left - 60, unitStatus.unitRect.top - 50, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransOverlord)
	{
		// 빈 if문으로 이 부분의 렌더를 피하게 함
	}
	else if (isTransHydralisk)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left - 60, unitStatus.unitRect.top - 50, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransMutalisk)
	{
		// 빈 if문으로 이 부분의 렌더를 피하게 함
	}
	else if (isTransScourge)
	{
		// 빈 if문으로 이 부분의 렌더를 피하게 함
	}
	else if (isTransQueen)
	{
		// 빈 if문으로 이 부분의 렌더를 피하게 함
	}
	else if (isTransUltralisk)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left - 60, unitStatus.unitRect.top - 110, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}	
	else if (isTransDefiler)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left - 60, unitStatus.unitRect.top - 110, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else
	{
		if (unitStatus.playerNumber == PLAYER1)
		{
			unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left, unitStatus.unitRect.top, unitStatus.frameIndexX, unitStatus.frameIndexY);
		}
		else if (unitStatus.playerNumber == PLAYER2)
		{
			unitStatus.enemyUnitImage1->FrameRender(hdc, unitStatus.unitRect.left, unitStatus.unitRect.top, unitStatus.frameIndexX, unitStatus.frameIndexY);
		}
	}
}

void Larva::RenderUI(HDC hdc)
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
		commandImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
		commandImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
		commandImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
		commandImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top);
		commandImage[SLOT5]->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
		commandImage[SLOT6]->Render(hdc, commandRect[SLOT6].left, commandRect[SLOT6].top);
		commandImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
		commandImage[SLOT8]->Render(hdc, commandRect[SLOT8].left, commandRect[SLOT8].top);
		commandImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);
	}
}

void Larva::RenderAirUint(HDC hdc)
{
	if (isTransOverlord)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left - 60, unitStatus.unitRect.top-120, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransMutalisk)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left - 60, unitStatus.unitRect.top - 120, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
	else if (isTransScourge)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left - 60, unitStatus.unitRect.top - 120, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}	
	else if (isTransQueen)
	{
		unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left - 60, unitStatus.unitRect.top - 120, unitStatus.frameIndexX, unitStatus.frameIndexY);
	}
}

void Larva::PlayAnimation()
{
	if (isTransDrone)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransDrone = false;
				commandSlot[SLOT1]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT1]->Update();
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransZergling)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransZergling = false;
				commandSlot[SLOT2]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT2]->Update();
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransOverlord)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransOverlord = false;
				commandSlot[SLOT3]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT3]->Update();
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransHydralisk)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransHydralisk = false;
				commandSlot[SLOT4]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT4]->Update();
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransMutalisk)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransMutalisk = false;
				commandSlot[SLOT5]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT5]->Update();
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransScourge)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransScourge = false;
				commandSlot[SLOT6]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT6]->Update();
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransQueen)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransQueen = false;
				commandSlot[SLOT7]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT7]->Update();
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransUltralisk)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX()-1)
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransUltralisk = false;
				commandSlot[SLOT8]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT8]->Update();
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
	else if (isTransDefiler)
	{
		unitStatus.frameIndexY = 0;
		unitStatus.frameCount++;
		unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
		if (unitStatus.frameCount % 4 == 0)
		{
			unitStatus.frameCount = 0;
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
				isTransform = true;
				isTransDefiler = false;
				commandSlot[SLOT9]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT9]->Update();
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
			if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
			{
				unitStatus.frameIndexX = 0;
			}
			unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
			unitStatus.frameIndexX++;
		}
	}
}

