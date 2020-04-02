#include "stdafx.h"
#include "EvolutionChamber.h"


EvolutionChamber::EvolutionChamber()
{
}


EvolutionChamber::~EvolutionChamber()
{
}

EvolutionChamber::EvolutionChamber(int _playerNumber, POINT buildXY)
{
	progressBar = new ProgressBar;

	buildStatus.buidKind = EVOLUTIONCHAMBER;

	buildStatus.playerNumber = _playerNumber;

	buildStatus.buildingMaxHp = 750;
	buildStatus.buildingCurrentHp = 750;
	buildStatus.buildingAtk = 0;
	buildStatus.buildingDef = 1;
	buildStatus.buildTime = 40;

	buildStatus.buildingMineralPrice = 75;
	buildStatus.buildingGasPrice = 0;

	buildStatus.buildImage = IMAGEMANAGER->FindImage("EvolutionChamber");
	//buildStatus.enemyBuildImage1 = IMAGEMANAGER->FindImage("EnemyHatchery");
	buildStatus.buildingSelectImage = IMAGEMANAGER->FindImage("3X2");
	buildStatus.buildingWireFrame = IMAGEMANAGER->FindImage("EvolutionWirefram");
	buildStatus.buildingFrontProgressImage = IMAGEMANAGER->FindImage("ZergProgressFront");
	buildStatus.buildingBackProgressImage = IMAGEMANAGER->FindImage("ZergProgressBack");

	buildStatus.buildRect = RectMake(buildXY.x, buildXY.y, 64 * 3, 64 * 2);
	buildStatus.buildCollisionRect = RectMake(buildXY.x, buildXY.y + 64, 64 * 3, 64);

	// 지어진 건물 위치 블록처리 for 문의 i 값은 가로 최대 수치 내부의 SetBlockTile은 세로를 설정해준다.
	for (int i = 0; i < 3; i++)
	{
		PLAYERMANAGER->SetBlockTile(buildXY.x + buildXY.y / TILEX + TILEX * i);
		PLAYERMANAGER->SetBlockTile(buildXY.x + buildXY.y / TILEX + TILEX * i + 1);
	}

	buildStatus.buildRectX = buildStatus.buildRect.left + (buildStatus.buildRect.right - buildStatus.buildRect.left) / 2;
	buildStatus.buildRectY = buildStatus.buildRect.top + (buildStatus.buildRect.bottom - buildStatus.buildRect.top) / 2;

	buildStatus.buildingImageWidthHalf = buildStatus.buildImage->GetWidth() / 2;
	buildStatus.buildingImageHeightHalf = buildStatus.buildImage->GetHeight() / 2;

	buildStatus.buildingSelectImageWidth = buildStatus.buildingSelectImage->GetWidth() / 2;
	buildStatus.buildingSelectImageHeight = buildStatus.buildingSelectImage->GetHeight() / 2;

	buildStatus.buildingProgressWidth = buildStatus.buildingBackProgressImage->GetWidth() / 2;
	buildStatus.buildingProgressHeight = buildStatus.buildingBackProgressImage->GetHeight() / 2;

	buildStatus.frameCount = 0;
	buildStatus.frameIndexX = 0;
	buildStatus.frameIndexY = 0;

	buildStatus.buildingPortraitsImage = IMAGEMANAGER->FindImage("portraitsOverMind");
	buildStatus.buildingPortraitsCount = 0;
	buildStatus.buildingPortraitsFrameY = 0;

	isClick = false;

	progressBar->Init("images/UI/ZergProgressFront.bmp", "images/UI/ZergProgressBack.bmp", buildStatus.buildRect.left, buildStatus.buildRect.bottom, 107 * 2, 9 * 2);

	// 명령 이미지 설정
	commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");
	commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");
	commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");

	meleeAttackDescription = IMAGEMANAGER->FindImage("upgradeMeleeAttacks");
	missileAttackDescription = IMAGEMANAGER->FindImage("upgradeMissileAttacks");
	carapaceDescription = IMAGEMANAGER->FindImage("evolveCarapace");

	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() - 1);
}

HRESULT EvolutionChamber::Init()
{
	return S_OK;
}

void EvolutionChamber::Release()
{
	SAFE_DELETE(progressBar);
}

void EvolutionChamber::Update()
{	
	// 애니메이션 프레임 업데이트
	PlayAnimation();
	PlayPortraits();

	if (BUILDMANAGER->GetHaveLair() || BUILDMANAGER->GetHaveHive())
	{
		commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");
		commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");
		commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");
	}

	// 해당 객체가 클릭 되었을 때
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		// 밀리 어택 업그레이드
		if (UPGRADEMANAGER->GetMeleeAttack() == 0)
		{
			commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");

			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT1] = IMAGEMANAGER->FindImage("ClickUpgradeMeleeAttackIcon");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 100 && PLAYERMANAGER->GetVespeneGas() >= 100)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UPGRADEMANAGER->SetMeleeAttack(1);
						PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 100);
						PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 100);
						commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('M'))
			{
				commandImage[SLOT1] = IMAGEMANAGER->FindImage("ClickUpgradeMeleeAttackIcon");
			}
			if (KEYMANAGER->IsOnceKeyUp('M'))
			{
				if (PLAYERMANAGER->GetMineral() >= 100 && PLAYERMANAGER->GetVespeneGas() >= 100)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UPGRADEMANAGER->SetMeleeAttack(1);
					PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 100);
					PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 100);
					commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");
				}
			}
		}
		else if (UPGRADEMANAGER->GetMeleeAttack() == 1 && BUILDMANAGER->GetHaveLair())
		{
			commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");

			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");

				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT1] = IMAGEMANAGER->FindImage("ClickUpgradeMeleeAttackIcon");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 150 && PLAYERMANAGER->GetVespeneGas() >= 150)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UPGRADEMANAGER->SetMeleeAttack(2);
						PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 150);
						PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 150);
						commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('M'))
			{
				commandImage[SLOT1] = IMAGEMANAGER->FindImage("ClickUpgradeMeleeAttackIcon");
			}
			if (KEYMANAGER->IsOnceKeyUp('M'))
			{
				if (PLAYERMANAGER->GetMineral() >= 150 && PLAYERMANAGER->GetVespeneGas() >= 150)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UPGRADEMANAGER->SetMeleeAttack(2);
					PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 150);
					PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 150);
					commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");
				}
			}
		}
		else if (UPGRADEMANAGER->GetMeleeAttack() == 2 && BUILDMANAGER->GetHaveHive())
		{
			commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");

			if (PtInRect(&commandRect[SLOT1], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT1] = IMAGEMANAGER->FindImage("ClickUpgradeMeleeAttackIcon");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 200 && PLAYERMANAGER->GetVespeneGas() >= 200)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UPGRADEMANAGER->SetMeleeAttack(3);
						PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 200);
						PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 200);
						commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('M'))
			{
				commandImage[SLOT1] = IMAGEMANAGER->FindImage("ClickUpgradeMeleeAttackIcon");
			}
			if (KEYMANAGER->IsOnceKeyUp('M'))
			{
				if (PLAYERMANAGER->GetMineral() >= 200 && PLAYERMANAGER->GetVespeneGas() >= 200)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UPGRADEMANAGER->SetMeleeAttack(3);
					PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 200);
					PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 200);
					commandImage[SLOT1] = IMAGEMANAGER->FindImage("upgradeMeleeAttackIcon");
				}
			}
		}
		else
		{
			commandImage[SLOT1] = IMAGEMANAGER->FindImage("DisabledUpgradeMeleeAttackIcon");
		}

		// 미사일 어택 업그레이드
		if (UPGRADEMANAGER->GetMissileAttack() == 0)
		{
			commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");

			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT2] = IMAGEMANAGER->FindImage("ClickUpgradeMissileAttackIcon");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 100 && PLAYERMANAGER->GetVespeneGas() >= 100)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UPGRADEMANAGER->SetMissileAttack(1);
						PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 100);
						PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 100);
						commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('A'))
			{
				commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");
			}
			if (KEYMANAGER->IsOnceKeyUp('A'))
			{
				if (PLAYERMANAGER->GetMineral() >= 100 && PLAYERMANAGER->GetVespeneGas() >= 100)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UPGRADEMANAGER->SetMissileAttack(1);
					PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 100);
					PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 100);
					commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");
				}
			}
		}
		else if (UPGRADEMANAGER->GetMissileAttack() == 1 && BUILDMANAGER->GetHaveLair())
		{
			commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");

			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{
				commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");

				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT2] = IMAGEMANAGER->FindImage("ClickUpgradeMissileAttackIcon");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 150 && PLAYERMANAGER->GetVespeneGas() >= 150)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UPGRADEMANAGER->SetMissileAttack(2);
						PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 150);
						PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 150);
						commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('A'))
			{
				commandImage[SLOT2] = IMAGEMANAGER->FindImage("ClickUpgradeMissileAttackIcon");
			}
			if (KEYMANAGER->IsOnceKeyUp('A'))
			{
				if (PLAYERMANAGER->GetMineral() >= 150 && PLAYERMANAGER->GetVespeneGas() >= 150)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UPGRADEMANAGER->SetMissileAttack(2);
					PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 150);
					PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 150);
					commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");
				}
			}
		}
		else if (UPGRADEMANAGER->GetMissileAttack() == 2 && BUILDMANAGER->GetHaveHive())
		{
			commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");

			if (PtInRect(&commandRect[SLOT2], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT2] = IMAGEMANAGER->FindImage("ClickUpgradeMissileAttackIcon");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 200 && PLAYERMANAGER->GetVespeneGas() >= 200)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UPGRADEMANAGER->SetMissileAttack(3);
						PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 200);
						PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 200);
						commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('A'))
			{
				commandImage[SLOT2] = IMAGEMANAGER->FindImage("ClickUpgradeMissileAttackIcon");
			}
			if (KEYMANAGER->IsOnceKeyUp('A'))
			{
				if (PLAYERMANAGER->GetMineral() >= 200 && PLAYERMANAGER->GetVespeneGas() >= 200)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UPGRADEMANAGER->SetMissileAttack(3);
					PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 200);
					PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 200);
					commandImage[SLOT2] = IMAGEMANAGER->FindImage("upgradeMissileAttackIcon");
				}
			}
		}
		else
		{
			commandImage[SLOT2] = IMAGEMANAGER->FindImage("DisabledUpgradeMissileAttackIcon");
		}

		// 표피 업그레이드
		if (UPGRADEMANAGER->GetEvolveCarapace() == 0)
		{
			commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");

			if (PtInRect(&commandRect[SLOT3], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT3] = IMAGEMANAGER->FindImage("ClickEvolveCarapaceIcon");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 150 && PLAYERMANAGER->GetVespeneGas() >= 150)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UPGRADEMANAGER->SetEvolveCarapace(1);
						PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 150);
						PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 150);
						commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('C'))
			{
				commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");
			}
			if (KEYMANAGER->IsOnceKeyUp('C'))
			{
				if (PLAYERMANAGER->GetMineral() >= 1500 && PLAYERMANAGER->GetVespeneGas() >= 150)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UPGRADEMANAGER->SetEvolveCarapace(1);
					PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 150);
					PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 150);
					commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");
				}
			}
		}
		else if (UPGRADEMANAGER->GetEvolveCarapace() == 1 && BUILDMANAGER->GetHaveLair())
		{
			commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");

			if (PtInRect(&commandRect[SLOT3], m_ptMouse))
			{
				commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");

				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT3] = IMAGEMANAGER->FindImage("ClickEvolveCarapaceIcon");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 225 && PLAYERMANAGER->GetVespeneGas() >= 225)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UPGRADEMANAGER->SetEvolveCarapace(2);
						PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 225);
						PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 225);
						commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('C'))
			{
				commandImage[SLOT3] = IMAGEMANAGER->FindImage("ClickEvolveCarapaceIcon");
			}
			if (KEYMANAGER->IsOnceKeyUp('C'))
			{
				if (PLAYERMANAGER->GetMineral() >= 225 && PLAYERMANAGER->GetVespeneGas() >= 225)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UPGRADEMANAGER->SetEvolveCarapace(2);
					PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 225);
					PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 225);
					commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");
				}
			}
		}
		else if (UPGRADEMANAGER->GetEvolveCarapace() == 2 && BUILDMANAGER->GetHaveHive())
		{
			commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");

			if (PtInRect(&commandRect[SLOT3], m_ptMouse))
			{
				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					commandImage[SLOT3] = IMAGEMANAGER->FindImage("ClickEvolveCarapaceIcon");
				}
				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
				{
					if (PLAYERMANAGER->GetMineral() >= 300 && PLAYERMANAGER->GetVespeneGas() >= 300)
					{
						// 눌렸다는 명령을 true 해주는 것을 만든다.
						UPGRADEMANAGER->SetEvolveCarapace(3);
						PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 300);
						PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 300);
						commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");
					}
				}
			}
			if (KEYMANAGER->IsStayKeyDown('C'))
			{
				commandImage[SLOT3] = IMAGEMANAGER->FindImage("ClickEvolveCarapaceIcon");
			}
			if (KEYMANAGER->IsOnceKeyUp('C'))
			{
				if (PLAYERMANAGER->GetMineral() >= 300 && PLAYERMANAGER->GetVespeneGas() >= 300)
				{
					// 눌렸다는 명령을 true 해주는 것을 만든다.
					UPGRADEMANAGER->SetEvolveCarapace(3);
					PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 300);
					PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 300);
					commandImage[SLOT3] = IMAGEMANAGER->FindImage("evolveCarapaceIcon");
				}
			}
		}
		else
		{
			commandImage[SLOT3] = IMAGEMANAGER->FindImage("DisabledEvolveCarapaceIcon");
		}

	}

	// 슬롯 위치 카메라 반영
	SetCommandRect();

	progressBar->SetGauge(buildStatus.buildingCurrentHp, buildStatus.buildingMaxHp);
}

void EvolutionChamber::Render(HDC hdc)
{
	//해당 객체가 클릭 되었을 때
	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		buildStatus.buildingSelectImage->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingSelectImageWidth, buildStatus.buildRectY - buildStatus.buildingSelectImageHeight+20);
		progressBar->Render
		(hdc, buildStatus.buildRectX - buildStatus.buildingProgressWidth, buildStatus.buildRect.bottom + 20);
	}

	if (buildStatus.playerNumber == PLAYER1)
	{
		buildStatus.buildImage->FrameRender(hdc, buildStatus.buildRect.left - 30, buildStatus.buildRect.top - 40, buildStatus.frameIndexX, buildStatus.frameIndexY);
	}
	else if (buildStatus.playerNumber == PLAYER2)
	{
		buildStatus.enemyBuildImage1->FrameRender(hdc, buildStatus.buildRect.left, buildStatus.buildRect.top - 40, buildStatus.frameIndexX, buildStatus.frameIndexY);
	}
}

void EvolutionChamber::RenderUI(HDC hdc)
{
	buildStatus.buildingPortraitsImage->FrameRender(hdc, CAMERAMANAGER->GetCameraCenter().x + 170, CAMERAMANAGER->GetCameraCenter().y + 310, buildStatus.buildingPortraitsFrameX, buildStatus.buildingPortraitsFrameY);

	if (isClick && buildStatus.playerNumber == PLAYER1)
	{
		buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

		if (KEYMANAGER->IsToggleKey(VK_TAB))
		{
			for (int i = 0; i < COMMANDMAX; i++)
			{
				Rectangle(hdc, commandRect[i].left, commandRect[i].top, commandRect[i].right, commandRect[i].bottom);
			}
		}

		if (UPGRADEMANAGER->GetMeleeAttack() < 3)
		{
			commandImage[SLOT1]->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
		}
		if (UPGRADEMANAGER->GetMissileAttack() < 3)
		{
			commandImage[SLOT2]->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
		}
		if (UPGRADEMANAGER->GetEvolveCarapace() < 3)
		{
			commandImage[SLOT3]->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
		}

		if (PtInRect(&commandRect[SLOT1], m_ptMouse))
		{
			if (UPGRADEMANAGER->GetMeleeAttack() == 0)
			{
				meleeAttackDescription->Render(hdc, commandRect[SLOT1].left - meleeAttackDescription->GetWidth() * 0.5, commandRect[SLOT1].top - meleeAttackDescription->GetHeight());
				meleeAttackDescription = IMAGEMANAGER->FindImage("upgradeMeleeAttacks");
			}
			else if (UPGRADEMANAGER->GetMeleeAttack() == 1 && !BUILDMANAGER->GetHaveLair())
			{
				meleeAttackDescription->Render(hdc, commandRect[SLOT1].left - meleeAttackDescription->GetWidth() * 0.5, commandRect[SLOT1].top - meleeAttackDescription->GetHeight());
				meleeAttackDescription = IMAGEMANAGER->FindImage("meleeAttacksL2Require");
			}
			else if (UPGRADEMANAGER->GetMeleeAttack() == 1 && BUILDMANAGER->GetHaveLair())
			{
				meleeAttackDescription->Render(hdc, commandRect[SLOT1].left - meleeAttackDescription->GetWidth() * 0.5, commandRect[SLOT1].top - meleeAttackDescription->GetHeight());
				meleeAttackDescription = IMAGEMANAGER->FindImage("upgradeMeleeAttacks2");
			}
			else if (UPGRADEMANAGER->GetMeleeAttack() == 2 && !BUILDMANAGER->GetHaveHive())
			{
				meleeAttackDescription->Render(hdc, commandRect[SLOT1].left - meleeAttackDescription->GetWidth() * 0.5, commandRect[SLOT1].top - meleeAttackDescription->GetHeight());
				meleeAttackDescription = IMAGEMANAGER->FindImage("meleeAttacksL3Require");
			}
			else if (UPGRADEMANAGER->GetMeleeAttack() == 2 && BUILDMANAGER->GetHaveHive())
			{
				meleeAttackDescription->Render(hdc, commandRect[SLOT1].left - meleeAttackDescription->GetWidth() * 0.5, commandRect[SLOT1].top - meleeAttackDescription->GetHeight());
				meleeAttackDescription = IMAGEMANAGER->FindImage("upgradeMeleeAttacks3");
			}
			else
			{
				// 업그레이드가 완료되서 렌더를 하지 않는다.
			}
		}
		if (PtInRect(&commandRect[SLOT2], m_ptMouse))
		{
			if (UPGRADEMANAGER->GetMissileAttack() == 0)
			{
				missileAttackDescription->Render(hdc, commandRect[SLOT2].left - missileAttackDescription->GetWidth() * 0.5, commandRect[SLOT2].top - missileAttackDescription->GetHeight());
				missileAttackDescription = IMAGEMANAGER->FindImage("upgradeMissileAttacks");
			}
			else if (UPGRADEMANAGER->GetMissileAttack() == 1 && !BUILDMANAGER->GetHaveLair())
			{
				missileAttackDescription->Render(hdc, commandRect[SLOT2].left - missileAttackDescription->GetWidth() * 0.5, commandRect[SLOT2].top - missileAttackDescription->GetHeight());
				missileAttackDescription = IMAGEMANAGER->FindImage("missileAttacksL2Require");
			}
			else if (UPGRADEMANAGER->GetMissileAttack() == 1 && BUILDMANAGER->GetHaveLair())
			{
				missileAttackDescription->Render(hdc, commandRect[SLOT2].left - missileAttackDescription->GetWidth() * 0.5, commandRect[SLOT2].top - missileAttackDescription->GetHeight());
				missileAttackDescription = IMAGEMANAGER->FindImage("upgradeMissileAttacks2");
			}
			else if (UPGRADEMANAGER->GetMissileAttack() == 2 && !BUILDMANAGER->GetHaveHive())
			{
				missileAttackDescription->Render(hdc, commandRect[SLOT2].left - missileAttackDescription->GetWidth() * 0.5, commandRect[SLOT2].top - missileAttackDescription->GetHeight());
				missileAttackDescription = IMAGEMANAGER->FindImage("missileAttacksL3Require");
			}
			else if (UPGRADEMANAGER->GetMissileAttack() == 2 && BUILDMANAGER->GetHaveHive())
			{
				missileAttackDescription->Render(hdc, commandRect[SLOT2].left - missileAttackDescription->GetWidth() * 0.5, commandRect[SLOT2].top - missileAttackDescription->GetHeight());
				missileAttackDescription = IMAGEMANAGER->FindImage("upgradeMissileAttacks3");
			}
			else
			{
				// 업그레이드가 완료되서 렌더를 하지 않는다.
			}
		}
		if (PtInRect(&commandRect[SLOT3], m_ptMouse))
		{
			if (UPGRADEMANAGER->GetEvolveCarapace() == 0)
			{
				carapaceDescription->Render(hdc, commandRect[SLOT3].left - carapaceDescription->GetWidth() * 0.5 - 20, commandRect[SLOT3].top - carapaceDescription->GetHeight());
				carapaceDescription = IMAGEMANAGER->FindImage("evolveCarapace");
			}
			else if (UPGRADEMANAGER->GetEvolveCarapace() == 1 && !BUILDMANAGER->GetHaveLair())
			{
				carapaceDescription->Render(hdc, commandRect[SLOT3].left - carapaceDescription->GetWidth() * 0.5 - 20, commandRect[SLOT3].top - carapaceDescription->GetHeight());
				carapaceDescription = IMAGEMANAGER->FindImage("carapaceL2Requires");
			}
			else if (UPGRADEMANAGER->GetEvolveCarapace() == 1 && BUILDMANAGER->GetHaveLair())
			{
				carapaceDescription->Render(hdc, commandRect[SLOT3].left - carapaceDescription->GetWidth() * 0.5 - 20, commandRect[SLOT3].top - carapaceDescription->GetHeight());
				carapaceDescription = IMAGEMANAGER->FindImage("evolveCarapace2");
			}
			else if (UPGRADEMANAGER->GetEvolveCarapace() == 2 && !BUILDMANAGER->GetHaveHive())
			{
				carapaceDescription->Render(hdc, commandRect[SLOT3].left - carapaceDescription->GetWidth() * 0.5 - 20, commandRect[SLOT3].top - carapaceDescription->GetHeight());
				carapaceDescription = IMAGEMANAGER->FindImage("carapaceL3Requires");
			}
			else if (UPGRADEMANAGER->GetEvolveCarapace() == 2 && BUILDMANAGER->GetHaveHive())
			{
				carapaceDescription->Render(hdc, commandRect[SLOT3].left - carapaceDescription->GetWidth() * 0.5 - 20, commandRect[SLOT3].top - carapaceDescription->GetHeight());
				carapaceDescription = IMAGEMANAGER->FindImage("evolveCarapace3");
			}
			else
			{
				// 업그레이드가 완료되서 렌더를 하지 않는다.
			}
		}
		
		SetTextColor(hdc, RGB(0, 222, 0));
		sprintf_s(str, "%d", buildStatus.buildingCurrentHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 250, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));
		sprintf_s(str, "/  %d", buildStatus.buildingMaxHp);
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 200, CAMERAMANAGER->GetCameraCenter().y + 410, str, strlen(str));

		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(str, "Zerg EvolutionChamber");
		TextOut(hdc, CAMERAMANAGER->GetCameraCenter().x - 80, CAMERAMANAGER->GetCameraCenter().y + 290, str, strlen(str));
	}
}
