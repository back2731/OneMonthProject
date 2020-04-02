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
	unitStatus.unitCurrentHp = 25;
	unitStatus.unitAtk = 0;
	unitStatus.unitBaseAtk = 0;
	unitStatus.unitDef = 10;
	unitStatus.unitBaseDef = 10;
	unitStatus.unitTime = 0;

	unitStatus.unitMineralPrice = 50;
	unitStatus.unitGasPrice = 0;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("larva");
	unitStatus.enemyUnitImage1 = IMAGEMANAGER->FindImage("enemyLarva");
	unitStatus.unitWireFrame = IMAGEMANAGER->FindImage("larvaWirefram");
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

	descriptionImage[SLOT1] = IMAGEMANAGER->FindImage("morphToDrone");
	descriptionImage[SLOT2] = IMAGEMANAGER->FindImage("morphToZerglings");
	descriptionImage[SLOT3] = IMAGEMANAGER->FindImage("morphToOverlord");
	descriptionImage[SLOT4] = IMAGEMANAGER->FindImage("morphToHydralisk");
	descriptionImage[SLOT5] = IMAGEMANAGER->FindImage("morphToMutalisk");
	descriptionImage[SLOT6] = IMAGEMANAGER->FindImage("morphToScourge");
	descriptionImage[SLOT7] = IMAGEMANAGER->FindImage("morphToQueen");
	descriptionImage[SLOT8] = IMAGEMANAGER->FindImage("morphToUltralisk");
	descriptionImage[SLOT9] = IMAGEMANAGER->FindImage("morphTodefiler");
	abilityImage[SLOT1] = IMAGEMANAGER->FindImage("carapace");

	// 슬롯 위치 카메라 반영
	SetCommandRect();
	SetAbilityRect();
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
	if (CheckTrans())
	{
		isClick = false;
	}

	progressBar->SetGauge(unitStatus.unitCurrentHp, unitStatus.unitMaxHp);

	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		commandImage[SLOT1] = IMAGEMANAGER->FindImage("TransformDrone");
		
		// 드론 생산
		if (PtInRect(&commandRect[SLOT1], m_ptMouse))
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				commandImage[SLOT1] = IMAGEMANAGER->FindImage("ClickDrone");
			}
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				if (PLAYERMANAGER->GetCurrentPopulation() + 1 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice)
				{	
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UNITMANAGER->SetInputCommandTransDrone(true);
					commandImage[SLOT1] = IMAGEMANAGER->FindImage("TransformDrone");
				}
			}
			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
			{
				commandImage[SLOT1] = IMAGEMANAGER->FindImage("TransformDrone");
			}
		}
		if (KEYMANAGER->IsStayKeyDown('D'))
		{
			commandImage[SLOT1] = IMAGEMANAGER->FindImage("ClickDrone");
		}
		if (KEYMANAGER->IsOnceKeyDown('D'))
		{
			if (PLAYERMANAGER->GetCurrentPopulation() + 1 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice)
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransDrone(true);
			}
		}
		if (KEYMANAGER->IsOnceKeyUp('D'))
		{
			commandImage[SLOT1] = IMAGEMANAGER->FindImage("TransformDrone");
		}
		if (UNITMANAGER->GetInputCommandTransDrone())
		{
			isClick = false;

			isTransDrone = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("droneBirth");
		}

		// 저글링 생산
		if (BUILDMANAGER->GetHaveSpawningpool())
		{
			commandImage[SLOT2] = IMAGEMANAGER->FindImage("TransformZergling");
			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT2] = IMAGEMANAGER->FindImage("ClickZergling");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetCurrentPopulation() + 1 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UNITMANAGER->SetInputCommandTransZergling(true);
						commandImage[SLOT2] = IMAGEMANAGER->FindImage("TransformZergling");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('Z'))
			{
				commandImage[SLOT2] = IMAGEMANAGER->FindImage("ClickZergling");
			}
			if (KEYMANAGER->IsOnceKeyUp('Z'))
			{
				if (PLAYERMANAGER->GetCurrentPopulation() + 1 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UNITMANAGER->SetInputCommandTransZergling(true);
					commandImage[SLOT2] = IMAGEMANAGER->FindImage("TransformZergling");
				}
			}
			if (UNITMANAGER->GetInputCommandTransZergling())
			{
				isClick = false;

				isTransZergling = true;

				unitStatus.unitImage = IMAGEMANAGER->FindImage("zerglingBirth");
			}
		}
		else
		{
			commandImage[SLOT2] = IMAGEMANAGER->FindImage("DisabledZergling");
		}

		// 오버로드 생산
		if (PtInRect(&commandRect[SLOT3], m_ptMouse))
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				commandImage[SLOT3] = IMAGEMANAGER->FindImage("ClickOverlord");
			}
			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
			{
				if (PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UNITMANAGER->SetInputCommandTransOverlord(true);
				}
				commandImage[SLOT3] = IMAGEMANAGER->FindImage("TransformOverlord");
			}

		}
		if (KEYMANAGER->IsStayKeyDown('O'))
		{
			commandImage[SLOT3] = IMAGEMANAGER->FindImage("ClickOverlord");
		}
		if (KEYMANAGER->IsOnceKeyUp('O'))
		{
			if (PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice)
			{
				// 눌렸다는 명령을 true 해주는 것을 만든다.
				UNITMANAGER->SetInputCommandTransOverlord(true);
			}
			commandImage[SLOT3] = IMAGEMANAGER->FindImage("TransformOverlord");
		}
		if (UNITMANAGER->GetInputCommandTransOverlord())
		{
			isClick = false;

			isTransOverlord = true;

			unitStatus.unitImage = IMAGEMANAGER->FindImage("overlordBirth");
		}
		
		// 히드라 생산
		if (BUILDMANAGER->GetHaveHydraliskden())
		{
			commandImage[SLOT4] = IMAGEMANAGER->FindImage("TransformHydralisk");

			if (PtInRect(&commandRect[SLOT4], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT4] = IMAGEMANAGER->FindImage("ClickHydralisk");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetCurrentPopulation() + 1 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UNITMANAGER->SetInputCommandTransHydralisk(true);
					}
					commandImage[SLOT4] = IMAGEMANAGER->FindImage("TransformHydralisk");
				}

			}
			if (KEYMANAGER->IsStayKeyDown('H'))
			{
				commandImage[SLOT4] = IMAGEMANAGER->FindImage("ClickHydralisk");
			}
			if (KEYMANAGER->IsOnceKeyUp('H'))
			{
				if (PLAYERMANAGER->GetCurrentPopulation() + 1 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UNITMANAGER->SetInputCommandTransHydralisk(true);
				}
				commandImage[SLOT4] = IMAGEMANAGER->FindImage("TransformHydralisk");
			}
			if (UNITMANAGER->GetInputCommandTransHydralisk())
			{
				isClick = false;

				isTransHydralisk = true;

				unitStatus.unitImage = IMAGEMANAGER->FindImage("hydraBirth");
			}
		}
		else
		{
			commandImage[SLOT4] = IMAGEMANAGER->FindImage("DisabledHydralisk");
		}

		// 뮤탈리스크 생산
		if (BUILDMANAGER->GetHaveSpire())
		{
			commandImage[SLOT5] = IMAGEMANAGER->FindImage("TransformMutalisk");
			commandImage[SLOT6] = IMAGEMANAGER->FindImage("TransformScourge");
			
			if (PtInRect(&commandRect[SLOT5], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT5] = IMAGEMANAGER->FindImage("ClickMutalisk");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetCurrentPopulation() + 2 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UNITMANAGER->SetInputCommandTransMutalisk(true);
					}
					commandImage[SLOT5] = IMAGEMANAGER->FindImage("TransformMutalisk");
				}

			}
			if (KEYMANAGER->IsStayKeyDown('M'))
			{
				commandImage[SLOT5] = IMAGEMANAGER->FindImage("ClickMutalisk");
			}
			if (KEYMANAGER->IsOnceKeyUp('M'))
			{
				if (PLAYERMANAGER->GetCurrentPopulation() + 2 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UNITMANAGER->SetInputCommandTransMutalisk(true);
				}
				commandImage[SLOT5] = IMAGEMANAGER->FindImage("TransformMutalisk");
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
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT6] = IMAGEMANAGER->FindImage("ClickScourge");
				}
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetCurrentPopulation() + 1 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UNITMANAGER->SetInputCommandTransScourge(true);
					}
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					commandImage[SLOT6] = IMAGEMANAGER->FindImage("TransformScourge");
				}

			}
			if (KEYMANAGER->IsStayKeyDown('S'))
			{
				commandImage[SLOT6] = IMAGEMANAGER->FindImage("ClickScourge");
			}
			if (KEYMANAGER->IsOnceKeyDown('S'))
			{
				if (PLAYERMANAGER->GetCurrentPopulation() + 1 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UNITMANAGER->SetInputCommandTransScourge(true);
				}
			}
			if (KEYMANAGER->IsOnceKeyUp('S'))
			{
				commandImage[SLOT6] = IMAGEMANAGER->FindImage("TransformScourge");
			}
			if (UNITMANAGER->GetInputCommandTransScourge())
			{
				isClick = false;

				isTransScourge = true;

				unitStatus.unitImage = IMAGEMANAGER->FindImage("scourgeBirth");
			}
		}
		else
		{
			commandImage[SLOT5] = IMAGEMANAGER->FindImage("DisabledMutalisk");
			commandImage[SLOT6] = IMAGEMANAGER->FindImage("DisabledScourge");
		}

		// 퀸 생산
		if (BUILDMANAGER->GetHaveQueensnest())
		{
			commandImage[SLOT7] = IMAGEMANAGER->FindImage("TransformQueen");
			if (PtInRect(&commandRect[SLOT7], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT7] = IMAGEMANAGER->FindImage("ClickQueen");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetCurrentPopulation() + 2 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UNITMANAGER->SetInputCommandTransQueen(true);
					}
					commandImage[SLOT7] = IMAGEMANAGER->FindImage("TransformQueen");
				}
			}
			if (KEYMANAGER->IsStayKeyDown('Q'))
			{
				commandImage[SLOT7] = IMAGEMANAGER->FindImage("ClickQueen");
			}
			if (KEYMANAGER->IsOnceKeyUp('Q'))
			{
				if (PLAYERMANAGER->GetCurrentPopulation() + 2 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UNITMANAGER->SetInputCommandTransQueen(true);
				}
				commandImage[SLOT7] = IMAGEMANAGER->FindImage("TransformQueen");
			}
			if (UNITMANAGER->GetInputCommandTransQueen())
			{
				isClick = false;

				isTransQueen = true;

				unitStatus.unitImage = IMAGEMANAGER->FindImage("queenBirth");
			}
		}
		else
		{
			commandImage[SLOT7] = IMAGEMANAGER->FindImage("DisabledQueen");
		}


		// 울트라리스크 생산
		if (BUILDMANAGER->GetHaveUltraliskcavern())
		{
			commandImage[SLOT8] = IMAGEMANAGER->FindImage("TransformUltralisk");
		
			if (PtInRect(&commandRect[SLOT8], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT8] = IMAGEMANAGER->FindImage("ClickUltralisk");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{						
					if (PLAYERMANAGER->GetCurrentPopulation() + 4 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UNITMANAGER->SetInputCommandTransUltralisk(true);
					}

					commandImage[SLOT8] = IMAGEMANAGER->FindImage("TransformUltralisk");
				}
			}
			if (KEYMANAGER->IsStayKeyDown('U'))
			{
				commandImage[SLOT8] = IMAGEMANAGER->FindImage("ClickUltralisk");
			}
			if (KEYMANAGER->IsOnceKeyUp('U'))
			{
				if (PLAYERMANAGER->GetCurrentPopulation() + 4 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UNITMANAGER->SetInputCommandTransUltralisk(true);
				}
				commandImage[SLOT8] = IMAGEMANAGER->FindImage("TransformUltralisk");
			}
			if (UNITMANAGER->GetInputCommandTransUltralisk())
			{
				isClick = false;

				isTransUltralisk = true;

				unitStatus.unitImage = IMAGEMANAGER->FindImage("ultraBirth");
			}
			
		}
		else
		{
			commandImage[SLOT8] = IMAGEMANAGER->FindImage("DisabledUltralisk");
		}

		// 디파일러 생산
		if (BUILDMANAGER->GetHaveDefilerMound())
		{
			commandImage[SLOT9] = IMAGEMANAGER->FindImage("TransformDefiler");
			if (PtInRect(&commandRect[SLOT9], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT9] = IMAGEMANAGER->FindImage("ClickDefiler");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetCurrentPopulation() + 2 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UNITMANAGER->SetInputCommandTransDefiler(true);
					}
					commandImage[SLOT9] = IMAGEMANAGER->FindImage("TransformDefiler");
				}
			}
			if (KEYMANAGER->IsStayKeyDown('F'))
			{
				commandImage[SLOT9] = IMAGEMANAGER->FindImage("ClickDefiler");
			}
			if (KEYMANAGER->IsOnceKeyUp('F'))
			{
				if (PLAYERMANAGER->GetCurrentPopulation() + 2 <= PLAYERMANAGER->GetmaxPopulation() && PLAYERMANAGER->GetMineral() >= unitStatus.unitMineralPrice && PLAYERMANAGER->GetVespeneGas() >= unitStatus.unitGasPrice)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UNITMANAGER->SetInputCommandTransDefiler(true);
				}
				commandImage[SLOT9] = IMAGEMANAGER->FindImage("TransformDefiler");
			}
			if (UNITMANAGER->GetInputCommandTransDefiler())
			{
				isClick = false;

				isTransDefiler = true;

				unitStatus.unitImage = IMAGEMANAGER->FindImage("defilerBirth");
			}
		}
		else
		{
			commandImage[SLOT9] = IMAGEMANAGER->FindImage("DisabledDefiler");
		}
	}

	PlayAnimation();

	unitStatus.unitDef = 0 + UPGRADEMANAGER->GetEvolveCarapace();

}

void Larva::Render(HDC hdc)
{
	if (isClick && unitStatus.playerNumber == PLAYER1)
	{
		unitStatus.unitSelectImage->Render(hdc, unitStatus.unitRectX - unitStatus.unitSelectImageWidth, unitStatus.unitRectY - unitStatus.unitSelectImageHeight);
		progressBar->Render(hdc, unitStatus.unitRectX - unitStatus.unitProgressWidth, unitStatus.unitRectY + 20);
	}
	else if (isClick && unitStatus.playerNumber == PLAYER2)
	{
		unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("enemy1X1");
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
	SetAbilityRect();

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
		commandImage[SLOT6]->Render(hdc, commandRect[SLOT6].left, commandRect[SLOT6].top);
		commandImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
		commandImage[SLOT8]->Render(hdc, commandRect[SLOT8].left, commandRect[SLOT8].top);
		commandImage[SLOT9]->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);

		if (PtInRect(&commandRect[SLOT1], m_ptMouse))
		{
			descriptionImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].bottom);
		}
		if (PtInRect(&commandRect[SLOT2], m_ptMouse))
		{
			if (BUILDMANAGER->GetHaveSpawningpool())
			{
				descriptionImage[SLOT2] = IMAGEMANAGER->FindImage("morphToZerglings");
				descriptionImage[SLOT2]->Render(hdc, commandRect[SLOT2].left - descriptionImage[SLOT2]->GetWidth() / 2, commandRect[SLOT2].bottom);
			}
			else
			{
				descriptionImage[SLOT2] = IMAGEMANAGER->FindImage("zerglingsRequires");
				descriptionImage[SLOT2]->Render(hdc, commandRect[SLOT2].left - descriptionImage[SLOT2]->GetWidth() / 2, commandRect[SLOT2].bottom);
			}
		}
		if (PtInRect(&commandRect[SLOT3], m_ptMouse))
		{
			descriptionImage[SLOT3]->Render(hdc, commandRect[SLOT3].left - descriptionImage[SLOT3]->GetWidth() + 50, commandRect[SLOT3].bottom);
		}
		if (PtInRect(&commandRect[SLOT4], m_ptMouse))
		{
			if (BUILDMANAGER->GetHaveHydraliskden())
			{
				descriptionImage[SLOT4] = IMAGEMANAGER->FindImage("morphToHydralisk");
				descriptionImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top - descriptionImage[SLOT4]->GetHeight());
			}
			else
			{
				descriptionImage[SLOT4] = IMAGEMANAGER->FindImage("hydraliskRequires");
				descriptionImage[SLOT4]->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top - descriptionImage[SLOT4]->GetHeight());
			}
		}
		if (PtInRect(&commandRect[SLOT5], m_ptMouse))
		{
			if (BUILDMANAGER->GetHaveSpire())
			{
				descriptionImage[SLOT5] = IMAGEMANAGER->FindImage("morphToMutalisk");
				descriptionImage[SLOT5]->Render(hdc, commandRect[SLOT5].left - descriptionImage[SLOT5]->GetWidth() / 2, commandRect[SLOT5].top - descriptionImage[SLOT5]->GetHeight());
			}
			else
			{
				descriptionImage[SLOT5] = IMAGEMANAGER->FindImage("mutaliskRequires");
				descriptionImage[SLOT5]->Render(hdc, commandRect[SLOT5].left - descriptionImage[SLOT5]->GetWidth() / 2, commandRect[SLOT5].top - descriptionImage[SLOT5]->GetHeight());
			}
		}
		if (PtInRect(&commandRect[SLOT6], m_ptMouse))
		{
			if (BUILDMANAGER->GetHaveSpire())
			{
				descriptionImage[SLOT6] = IMAGEMANAGER->FindImage("morphToScourge");
				descriptionImage[SLOT6]->Render(hdc, commandRect[SLOT6].left - descriptionImage[SLOT6]->GetWidth() + 50, commandRect[SLOT6].top - descriptionImage[SLOT6]->GetHeight());
			}
			else
			{
				descriptionImage[SLOT6] = IMAGEMANAGER->FindImage("scourgeRequires");
				descriptionImage[SLOT6]->Render(hdc, commandRect[SLOT6].left - descriptionImage[SLOT6]->GetWidth() + 50, commandRect[SLOT6].top - descriptionImage[SLOT6]->GetHeight());
			}
		}
		if (PtInRect(&commandRect[SLOT7], m_ptMouse))
		{
			if (BUILDMANAGER->GetHaveQueensnest())
			{
				descriptionImage[SLOT7] = IMAGEMANAGER->FindImage("morphToQueen");
				descriptionImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top - descriptionImage[SLOT7]->GetHeight());
			}
			else
			{
				descriptionImage[SLOT7] = IMAGEMANAGER->FindImage("queenRequires");
				descriptionImage[SLOT7]->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top - descriptionImage[SLOT7]->GetHeight());
			}
		}
		if (PtInRect(&commandRect[SLOT8], m_ptMouse))
		{
			if (BUILDMANAGER->GetHaveUltraliskcavern())
			{
				descriptionImage[SLOT8] = IMAGEMANAGER->FindImage("morphToUltralisk");
				descriptionImage[SLOT8]->Render(hdc, commandRect[SLOT8].left - descriptionImage[SLOT8]->GetWidth() / 2, commandRect[SLOT8].top - descriptionImage[SLOT8]->GetHeight());
			}
			else
			{
				descriptionImage[SLOT8] = IMAGEMANAGER->FindImage("ultraliskRequires");
				descriptionImage[SLOT8]->Render(hdc, commandRect[SLOT8].left - descriptionImage[SLOT8]->GetWidth() / 2, commandRect[SLOT8].top - descriptionImage[SLOT8]->GetHeight());
			}
		}
		if (PtInRect(&commandRect[SLOT9], m_ptMouse))
		{
			if (BUILDMANAGER->GetHaveDefilerMound())
			{
				descriptionImage[SLOT9] = IMAGEMANAGER->FindImage("morphTodefiler");
				descriptionImage[SLOT9]->Render(hdc, commandRect[SLOT9].left - descriptionImage[SLOT9]->GetWidth() + 50, commandRect[SLOT9].top - descriptionImage[SLOT9]->GetHeight());
			}
			else
			{
				descriptionImage[SLOT9] = IMAGEMANAGER->FindImage("defilerRequires");
				descriptionImage[SLOT9]->Render(hdc, commandRect[SLOT9].left - descriptionImage[SLOT9]->GetWidth() + 50, commandRect[SLOT9].top - descriptionImage[SLOT9]->GetHeight());
			}
		}
		
		// 능력치 이미지 렌더
		abilityImage[SLOT1]->Render(hdc, abilityRect[SLOT1].left, abilityRect[SLOT1].top);

		SetTextColor(hdc, RGB(0, 222, 0));
		sprintf_s(str, "%d", unitStatus.unitCurrentHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 240, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		sprintf_s(str, "/   %d", unitStatus.unitMaxHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 200, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));

		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(str, "Zerg Larva");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 80, CAMERAMANAGER->GetCameraCenter().y + 290, str, strlen(str));

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

bool Larva::CheckTrans()
{
	if (isTransDrone) return true;
	if (isTransZergling) return true;
	if (isTransOverlord) return true;
	if (isTransHydralisk) return true;
	if (isTransMutalisk) return true;
	if (isTransScourge) return true;
	if (isTransQueen) return true;
	if (isTransUltralisk) return true;
	if (isTransDefiler) return true;
	
	return false;
}

