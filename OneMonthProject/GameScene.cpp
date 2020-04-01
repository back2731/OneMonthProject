#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

HRESULT GameScene::Init()
{
	LoadMap(0);
	buildingVector.reserve(1000);
	unitVector.reserve(1000);
	airUnitVector.reserve(1000);
	selectVector.reserve(50);
	

	consoleImage = IMAGEMANAGER->FindImage("ZergConsole");

	// 초기 해처리 생성
	buildingVector.push_back(BUILDMANAGER->CreateHatchery(PLAYER1, { 64 * 7, 64 * 4 }));
	
	enemyBuildingVector.push_back(BUILDMANAGER->CreateHatchery(PLAYER2, { 64 * 2, 64 * 2 }));
	enemyBuildingVector.push_back(BUILDMANAGER->CreateHatchery(PLAYER2, { 64 * 7, 64 * 2 }));
	enemyBuildingVector.push_back(BUILDMANAGER->CreateHatchery(PLAYER2, { 64 * 12, 64 * 2 }));
	
	enemyUnitVector.push_back(UNITMANAGER->CreateZergling(PLAYER2, { 2200, 400 }));

	gas = RectMake(64 * 10, 64 * 8, 64 * 4, 64 * 2);

	for (int i = 0; i < TILESIZE; i++)
	{
		if (IntersectRect(&tempRect, &_tileMap[i].rect, &gas))
		{
			_tileMap[i].gas = true;
			PLAYERMANAGER->SetGasTile(i);
		}
	}

	// 해당 건물이 해처리라면 라바를 세팅해준다
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetBuildKind() == HATCHERY)
		{
			if (buildingVector[i]->GetBuildingPlayerNumber() == PLAYER1)
			{
				unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER1, { buildingVector[i]->GetBuildingRectX() - 70, buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 1));
				unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER1, { buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 2));
				unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER1, { buildingVector[i]->GetBuildingRectX() + 70, buildingVector[i]->GetBuildingRect().bottom + 20 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 3));

				buildingVector[i]->SetCurrentLarva(LARVAMAX);
			}
		}
	}

	mineralImage = IMAGEMANAGER->FindImage("mineral");
	vespeneGasImage = IMAGEMANAGER->FindImage("gas");
	populationImage = IMAGEMANAGER->FindImage("population");
	/*PLAYERMANAGER->SetMineral(10000);
	PLAYERMANAGER->SetVespeneGas(10000);*/

	maxPopulation = 9;
	return S_OK;
}

void GameScene::Release()
{
}

void GameScene::Update()
{
	CAMERAMANAGER->MoveCamera();

	if (KEYMANAGER->IsOnceKeyDown('P'))
	{
		PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() + 200);
		PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() + 200);
	}

	BUILDMANAGER->SetHaveHatchery(false);
	BUILDMANAGER->SetHaveLair(false);
	BUILDMANAGER->SetHaveHive(false);
	BUILDMANAGER->SetHaveSpawningpool(false);
	BUILDMANAGER->SetHaveHydraliskden(false);
	BUILDMANAGER->SetHaveEvolutionchamber(false);
	BUILDMANAGER->SetHaveCreepcolony(false);
	BUILDMANAGER->SetHaveSpire(false);
	BUILDMANAGER->SetHaveQueensnest(false);
	BUILDMANAGER->SetHaveUltraliskcavern(false);

	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetBuildKind() == HATCHERY)
		{
			BUILDMANAGER->SetHaveHatchery(true);
		}
		if (buildingVector[i]->GetBuildKind() == LAIR)
		{
			BUILDMANAGER->SetHaveHatchery(true);
			BUILDMANAGER->SetHaveLair(true);
		}
		if (buildingVector[i]->GetBuildKind() == HIVE)
		{
			BUILDMANAGER->SetHaveHatchery(true);
			BUILDMANAGER->SetHaveLair(true);
			BUILDMANAGER->SetHaveHive(true);
		}
		if (buildingVector[i]->GetBuildKind() == SPAWNINGPOOL)
		{
			BUILDMANAGER->SetHaveSpawningpool(true);
		}
		if (buildingVector[i]->GetBuildKind() == HYDRALISKDEN)
		{
			BUILDMANAGER->SetHaveHydraliskden(true);
		}
		if (buildingVector[i]->GetBuildKind() == EVOLUTIONCHAMBER)
		{
			BUILDMANAGER->SetHaveEvolutionchamber(true);
		}
		if (buildingVector[i]->GetBuildKind() == CREEPCOLONY)
		{
			BUILDMANAGER->SetHaveCreepcolony(true);
		}
		if (buildingVector[i]->GetBuildKind() == SPIRE)
		{
			BUILDMANAGER->SetHaveSpire(true);
		}
		if (buildingVector[i]->GetBuildKind() == QUEENSNEST)
		{
			BUILDMANAGER->SetHaveQueensnest(true);
		}
		if (buildingVector[i]->GetBuildKind() == ULTRALISKCAVERN)
		{
			BUILDMANAGER->SetHaveUltraliskcavern(true);
		}
		if (buildingVector[i]->GetBuildKind() == DEFILERMOUND)
		{
			BUILDMANAGER->SetHaveDefilerMound(true);
		}
	}

	ShowCursor(false);
	
	commandRect = RectMake(CAMERAMANAGER->GetCameraCenter().x + 335, CAMERAMANAGER->GetCameraCenter().y + 225, 250, 250);
	cameraRect1 = RectMake(CAMERAMANAGER->GetCameraXY().x - WINSIZEX, CAMERAMANAGER->GetCameraXY().y - WINSIZEY, WINSIZEX * 2, WINSIZEY * 2);
	cameraRect2 = RectMake(CAMERAMANAGER->GetCameraXY().x, CAMERAMANAGER->GetCameraXY().y, WINSIZEX, WINSIZEY);

	// 모든 건물 업데이트
	for (int i = 0; i < buildingVector.size(); i++)
	{
		buildingVector[i]->Update();
	}
	// 지상 유닛 업데이트
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->Update();
	}
	// 공중 유닛 업데이트
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		airUnitVector[i]->Update();
	}

	for (int i = 0; i < enemyBuildingVector.size(); i++)
	{
		enemyBuildingVector[i]->Update();
	}

	for (int i = 0; i < enemyUnitVector.size(); i++)
	{
		enemyUnitVector[i]->Update();
	}

	// 해당 건물을 클릭 했을 때 상태를 변경해주는 부분
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (PtInRect(&buildingVector[i]->GetBuildingRect(), m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				dragRect.left = m_ptMouse.x;
				dragRect.top = m_ptMouse.y;

				for (int j = 0; j < buildingVector.size(); j++)
				{
					buildingVector[j]->SetIsClick(false);
					buildingVector[i]->SetIsClick(true);
					
					for (int k = 0; k < unitVector.size(); k++)
					{
						unitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < airUnitVector.size(); k++)
					{
						airUnitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < enemyUnitVector.size(); k++)
					{
						enemyUnitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < enemyBuildingVector.size(); k++)
					{
						enemyBuildingVector[k]->SetIsClick(false);
					}
				}
			}
		}
	}

	// 해당 적 건물을 클릭 했을 때 상태를 변경해주는 부분
	for (int i = 0; i < enemyBuildingVector.size(); i++)
	{
		if (PtInRect(&enemyBuildingVector[i]->GetBuildingRect(), m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				dragRect.left = m_ptMouse.x;
				dragRect.top = m_ptMouse.y;

				for (int j = 0; j < enemyBuildingVector.size(); j++)
				{
					enemyBuildingVector[j]->SetIsClick(false);
					enemyBuildingVector[i]->SetIsClick(true);

					for (int k = 0; k < unitVector.size(); k++)
					{
						unitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < airUnitVector.size(); k++)
					{
						airUnitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < buildingVector.size(); k++)
					{
						buildingVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < enemyUnitVector.size(); k++)
					{
						enemyUnitVector[k]->SetIsClick(false);
					}
				}
			}
		}
	}

	// 해당 지상 유닛을 클릭 했을 때 상태를 변경해주는 부분
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (PtInRect(&unitVector[i]->GetUnitRect(), m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				dragRect.left = m_ptMouse.x;
				dragRect.top = m_ptMouse.y;

				for (int j = 0; j < unitVector.size(); j++)
				{
					unitVector[j]->SetIsClick(false);
					unitVector[i]->SetIsClick(true);

					for (int k = 0; k < buildingVector.size(); k++)
					{
						buildingVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < airUnitVector.size(); k++)
					{
						airUnitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < enemyUnitVector.size(); k++)
					{
						enemyUnitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < enemyBuildingVector.size(); k++)
					{
						enemyBuildingVector[k]->SetIsClick(false);
					}
				}
			}
		}
	}

	// 해당 공중 유닛을 클릭 했을 때 상태를 변경해주는 부분
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (PtInRect(&airUnitVector[i]->GetUnitRect(), m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				dragRect.left = m_ptMouse.x;
				dragRect.top = m_ptMouse.y;

				for (int j = 0; j < airUnitVector.size(); j++)
				{
					airUnitVector[j]->SetIsClick(false);
					airUnitVector[i]->SetIsClick(true);

					for (int k = 0; k < buildingVector.size(); k++)
					{
						buildingVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < unitVector.size(); k++)
					{
						unitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < enemyUnitVector.size(); k++)
					{
						enemyUnitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < enemyBuildingVector.size(); k++)
					{
						enemyBuildingVector[k]->SetIsClick(false);
					}
				}
			}
		}
	}

	// 해당 적 유닛을 클릭 했을 때 상태를 변경해주는 부분
	for (int i = 0; i < enemyUnitVector.size(); i++)
	{
		if (PtInRect(&enemyUnitVector[i]->GetUnitRect(), m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				dragRect.left = m_ptMouse.x;
				dragRect.top = m_ptMouse.y;

				for (int j = 0; j < enemyUnitVector.size(); j++)
				{
					enemyUnitVector[j]->SetIsClick(false);
					enemyUnitVector[i]->SetIsClick(true);

					for (int k = 0; k < buildingVector.size(); k++)
					{
						buildingVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < unitVector.size(); k++)
					{
						unitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < airUnitVector.size(); k++)
					{
						airUnitVector[k]->SetIsClick(false);
					}
					for (int k = 0; k < enemyBuildingVector.size(); k++)
					{
						enemyBuildingVector[k]->SetIsClick(false);
					}
				}
			}
		}
	}

	// 해처리(레어, 하이브)에서 셀렉트 라바를 눌렀을 때
	if (UNITMANAGER->GetSelectLarvaValue())
	{
		for (int i = 0; i < buildingVector.size(); i++)
		{
			buildingVector[i]->SetIsClick(false);
		}

		for (int i = 0; i < unitVector.size(); i++)
		{
			if (unitVector[i]->GetHatcheryX() == UNITMANAGER->GetSaveX() && unitVector[i]->GetHatcheryY() == UNITMANAGER->GetSaveY())
			{
				unitVector[i]->SetIsClick(true);
			}
		}
		UNITMANAGER->SetSelectLarva(false);
	}

	// 생산된 지상 유닛을 담은 벡터가 0보다 클때 함수를 통해 가져온다.
	if (UNITMANAGER->GetTempVector().size() > 0)
	{
		while (UNITMANAGER->GetTempVector().size() > 0)
		{
			unitVector.push_back(UNITMANAGER->ReturnUnitVector());
		}
	}

	// 생산된 공중 유닛을 담은 벡터가 0보다 클때 함수를 통해 가져온다.
	if (UNITMANAGER->GetAirUnitVector().size() > 0)
	{
		while (UNITMANAGER->GetAirUnitVector().size() > 0)
		{
			airUnitVector.push_back(UNITMANAGER->ReturnAirUnitVector());
		}
	}

	// 생산된 건물을 담은 벡터가 0보다 클때 함수를 통해 가져온다.
	if (BUILDMANAGER->GetTempVector().size() > 0)
	{
		while (BUILDMANAGER->GetTempVector().size() > 0)
		{
			buildingVector.push_back(BUILDMANAGER->ReturnBuildingVector());
		}
	}

	// 변태를 마치면 삭제 후 해처리 현재 라바 수 감소
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetUnitKind() == LARVA)
		{
			if (unitVector[i]->GetIsTransform())
			{
				unitVector[i]->SetIsClick(false);
				for (int j = 0; j < buildingVector.size(); j++)
				{
					if (unitVector[i]->GetHatcheryX() == buildingVector[j]->GetBuildingRectX() &&
						unitVector[i]->GetHatcheryY() == buildingVector[j]->GetBuildingRectY())
					{
						buildingVector[j]->SetCurrentLarva(-1);
					}
				}
				unitVector.erase(unitVector.begin() + i);
			}
		}
	}

	// 변태를 마치면 드론 벡터 삭제
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetUnitKind() == DRONE)
		{
			if (unitVector[i]->GetIsTransform())
			{
				unitVector.erase(unitVector.begin() + i);
			}
		}
	}

	// 라바 자동 생산 기능
	count++;
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetBuildingPlayerNumber() == PLAYER1 && 
			(buildingVector[i]->GetBuildKind() == HATCHERY || 
				buildingVector[i]->GetBuildKind() == LAIR || 
				buildingVector[i]->GetBuildKind() == HIVE))
		{
			if (buildingVector[i]->GetCurrentLarva() < LARVAMAX)
			{
				if (count % 200 == 0)
				{
					unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER1, { buildingVector[i]->GetBuildingRectX() - 70 + (70 * RND->GetInt(2)), buildingVector[i]->GetBuildingRect().bottom + 25 }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 1));
					buildingVector[i]->SetCurrentLarva(+1);
					count = 0;
				}
			}
		}
		if (buildingVector[i]->GetBuildingPlayerNumber() == PLAYER2)
		{
			if (buildingVector[i]->GetCurrentLarva() < LARVAMAX)
			{
				if (count % 200 == 0)
				{
					unitVector.push_back(UNITMANAGER->CreateLarva(PLAYER2, { buildingVector[i]->GetBuildingRectX() - 70 + (70 * RND->GetInt(2)), buildingVector[i]->GetBuildingRect().bottom + 25 + RND->GetInt(3) }, buildingVector[i]->GetBuildingRectX(), buildingVector[i]->GetBuildingRectY(), 1));
					buildingVector[i]->SetCurrentLarva(+1);
					count = 0;
				}
			}
		}
	}

	// 유닛간의 충돌처리 함수
	COLLISIONMANAGER->CollisionSameVector(airUnitVector, KNOCKBACK * 2, true);
	COLLISIONMANAGER->CollisionUnitToBuilding(unitVector, buildingVector);
	COLLISIONMANAGER->CollisionUnitToBuilding(unitVector, enemyBuildingVector);
	COLLISIONMANAGER->CollisionUnitToBuilding(enemyUnitVector, buildingVector);
	COLLISIONMANAGER->CollisionUnitToUnit(unitVector, enemyUnitVector);
	COLLISIONMANAGER->CollisionSameVector(unitVector, KNOCKBACK, true);
	COLLISIONMANAGER->CollisionSameVector(enemyUnitVector, KNOCKBACK, true);

	// 명령이 종료되면 false로 세팅하는 함수
	UNITMANAGER->SetInputCommandTransDrone(false);
	UNITMANAGER->SetInputCommandTransZergling(false);
	UNITMANAGER->SetInputCommandTransOverlord(false);
	UNITMANAGER->SetInputCommandTransHydralisk(false);
	UNITMANAGER->SetInputCommandTransMutalisk(false);
	UNITMANAGER->SetInputCommandTransScourge(false);
	UNITMANAGER->SetInputCommandTransQueen(false);
	UNITMANAGER->SetInputCommandTransUltralisk(false);
	UNITMANAGER->SetInputCommandTransDefiler(false);

	PLAYERMANAGER->SetInputCommandMove(false);

	// 드래그 명령문
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		dragRect.left = m_ptMouse.x;
		dragRect.top = m_ptMouse.y;
		dragRect.right = m_ptMouse.x;
		dragRect.bottom = m_ptMouse.y;

		if (!PtInRect(&commandRect, m_ptMouse))
		{
			for (int i = 0; i < buildingVector.size(); i++)
			{
				buildingVector[i]->SetIsClick(false);
			}
			for (int i = 0; i < unitVector.size(); i++)
			{
				unitVector[i]->SetIsClick(false);
			}
			for (int i = 0; i < airUnitVector.size(); i++)
			{
				airUnitVector[i]->SetIsClick(false);
			}
			for (int i = 0; i < enemyUnitVector.size(); i++)
			{
				enemyUnitVector[i]->SetIsClick(false);
			}
			for (int i = 0; i < enemyBuildingVector.size(); i++)
			{
				enemyBuildingVector[i]->SetIsClick(false);
			}
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		dragRect.right = m_ptMouse.x;
		dragRect.bottom = m_ptMouse.y;			
	}
	if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
	{
		dragRect.right = m_ptMouse.x;
		dragRect.bottom = m_ptMouse.y;
	}

	// 드래그된 지상 유닛 선택 명령문
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &dragRect, &unitVector[i]->GetUnitRect()))
		{
	 		unitVector[i]->SetIsClick(true);
			for (int i = 0; i < buildingVector.size(); i++)
			{
				buildingVector[i]->SetIsClick(false);
			}
		}
	}
	// 드래그된 공중 유닛 선택 명령문
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &dragRect, &airUnitVector[i]->GetUnitRect()))
		{
			airUnitVector[i]->SetIsClick(true);
			for (int i = 0; i < buildingVector.size(); i++)
			{
				buildingVector[i]->SetIsClick(false);
			}
		}
	}
	
	mineral = PLAYERMANAGER->GetMineral();
	vespeneGas = PLAYERMANAGER->GetVespeneGas();
	maxPopulation = PLAYERMANAGER->GetmaxPopulation();
	if (maxPopulation >= 200.f)
	{
		maxPopulation = 200.f;
	}
	currentPopulation = PLAYERMANAGER->GetCurrentPopulation();
	if (currentPopulation >= 200.f)
	{
		currentPopulation = 200.f;
	}
	if (currentPopulation < 0.f)
	{
		currentPopulation = 0.f;
	}

	if (PLAYERMANAGER->GetSearchPlayer().empty())
	{
		for (int i = 0; i < enemyUnitVector.size(); i++)
		{
			for (int j = 0; j < unitVector.size(); j++)
			{
				if (unitVector[j]->GetUnitKind() == ZERGLING)
				{
					if (IntersectRect(&tempRect, &enemyUnitVector[i]->GetUnitSearchingRect(), &unitVector[j]->GetUnitRect()))
					{
						PLAYERMANAGER->SetSearchPlayer(j);
						break;
					}
				}
			}
		}
	}
	else
	{
		if (!unitVector.empty())
		{
			for (int i = 0; i < enemyUnitVector.size(); i++)
			{
				if (enemyUnitVector[i]->GetUnitKind() == ZERGLING)
				{
					enemyUnitVector[i]->FindTrace(unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->GetUnitRectX(), unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->GetUnitRectY(), unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->GetUnitRect());

					if (IntersectRect(&tempRect, &enemyUnitVector[i]->GetUnitATKRect(), &unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->GetUnitRect()))
					{
						unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->SetUnitHp(unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->GetUnitHp() - enemyUnitVector[i]->GetUnitATK());
					
						COLLISIONMANAGER->CollisionSameVector(unitVector, KNOCKBACK, false);
						COLLISIONMANAGER->CollisionSameVector(enemyUnitVector, KNOCKBACK, false);
					
					}
					enemyUnitVector[i]->SetIsSearch(true);
					if (unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->GetUnitHp() <= 0)
					{
						if(unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->GetUnitKind() == ZERGLING)
						{
							PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() - 0.5f);
						}
						EFFECTMANAGER->Play("zerglingBlood", unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->GetUnitRectX(), unitVector[PLAYERMANAGER->ReturnSearchedPlayerNumber()]->GetUnitRectY());
						unitVector.erase(unitVector.begin() + PLAYERMANAGER->ReturnSearchedPlayerNumber());
						PLAYERMANAGER->EraseSearchPlayerVector();
						for (int i = 0; i < enemyUnitVector.size(); i++)
						{
							enemyUnitVector[i]->SetIsSearch(false);
							enemyUnitVector[i]->SetUnitState(IDLE);
						}
						break;
					}
				}
			}
		}
	}



	if (PLAYERMANAGER->GetSearchEnemy().empty())
	{
		for (int i = 0; i < unitVector.size(); i++)
		{
			for (int j = 0; j < enemyUnitVector.size(); j++)
			{
				if (IntersectRect(&tempRect, &unitVector[i]->GetUnitSearchingRect(), &enemyUnitVector[j]->GetUnitRect()))
				{				
					PLAYERMANAGER->SetSearchEnemy(j);
					break;
				}
			}
		}
	}
	else
	{
		if (!enemyUnitVector.empty())
		{
			for (int i = 0; i < unitVector.size(); i++)
			{
				if (unitVector[i]->GetUnitKind() == ZERGLING)
				{
					unitVector[i]->FindTrace(enemyUnitVector[PLAYERMANAGER->ReturnSearchedEnemyNumber()]->GetUnitRectX(), enemyUnitVector[PLAYERMANAGER->ReturnSearchedEnemyNumber()]->GetUnitRectY(), enemyUnitVector[PLAYERMANAGER->ReturnSearchedEnemyNumber()]->GetUnitRect());

					if (IntersectRect(&tempRect, &unitVector[i]->GetUnitATKRect(), &enemyUnitVector[PLAYERMANAGER->ReturnSearchedEnemyNumber()]->GetUnitRect()))
					{
						enemyUnitVector[PLAYERMANAGER->ReturnSearchedEnemyNumber()]->SetUnitHp(enemyUnitVector[PLAYERMANAGER->ReturnSearchedEnemyNumber()]->GetUnitHp() - unitVector[i]->GetUnitATK());
					
						COLLISIONMANAGER->CollisionSameVector(unitVector, KNOCKBACK, false);
						COLLISIONMANAGER->CollisionSameVector(enemyUnitVector, KNOCKBACK, false);
					}
					unitVector[i]->SetIsSearch(true);
					if (enemyUnitVector[PLAYERMANAGER->ReturnSearchedEnemyNumber()]->GetUnitHp() <= 0)
					{
						EFFECTMANAGER->Play("zerglingBlood", enemyUnitVector[PLAYERMANAGER->ReturnSearchedEnemyNumber()]->GetUnitRectX(), enemyUnitVector[PLAYERMANAGER->ReturnSearchedEnemyNumber()]->GetUnitRectY());

						enemyUnitVector.erase(enemyUnitVector.begin() + PLAYERMANAGER->ReturnSearchedEnemyNumber());
						PLAYERMANAGER->EraseSearchVector();
						for (int i = 0; i < unitVector.size(); i++)
						{
							unitVector[i]->SetIsSearch(false);
							unitVector[i]->SetUnitState(IDLE);
						}
						break;
					}
				}
			}
		}
	}	
	
	if (PLAYERMANAGER->GetSearchEnemy().empty() && PLAYERMANAGER->GetSearchEnemyBuilding().empty())
	{
		for (int i = 0; i < unitVector.size(); i++)
		{
			for (int j = 0; j < enemyBuildingVector.size(); j++)
			{
				if (IntersectRect(&tempRect, &unitVector[i]->GetUnitSearchingRect(), &enemyBuildingVector[j]->GetBuildingRect()) && searching)
				{
					PLAYERMANAGER->SetSearchEnemyBuilding(j);
					break;
				}
			}
		}
	}
	else if(PLAYERMANAGER->GetSearchEnemy().empty() && !PLAYERMANAGER->GetSearchEnemyBuilding().empty())
	{
		if (!enemyBuildingVector.empty())
		{
			for (int i = 0; i < unitVector.size(); i++)
			{
				if (unitVector[i]->GetUnitKind() == ZERGLING)
				{
					unitVector[i]->FindTrace(enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingRectX(), enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingRectY(), enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingRect());

					if (IntersectRect(&tempRect, &unitVector[i]->GetUnitATKRect(), &enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingRect()))
					{
						enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->SetBuildingHP(enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingHP() - unitVector[i]->GetUnitATK());
					}
					unitVector[i]->SetIsSearch(true);
					if (enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingHP() <= 0)
					{
						EFFECTMANAGER->Play("buildingWreck", enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingRectX(), enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingRectY());
						EFFECTMANAGER->Play("blood", enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingRectX(), enemyBuildingVector[PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber()]->GetBuildingRectY());

						enemyBuildingVector.erase(enemyBuildingVector.begin() + PLAYERMANAGER->ReturnSearchedEnemyBuildingNumber());
						PLAYERMANAGER->EraseSearchBuildingVector();
						for (int i = 0; i < unitVector.size(); i++)
						{
							unitVector[i]->SetIsSearch(false);
							unitVector[i]->SetUnitState(IDLE);
						}
						break;
					}
				}
			}
		}
	}
	if (KEYMANAGER->IsOnceKeyDown('J'))
	{
		EFFECTMANAGER->Play("buildingWreck", m_ptMouse.x, m_ptMouse.y);
		EFFECTMANAGER->Play("blood", m_ptMouse.x, m_ptMouse.y);
	}

	// 추적 정지 후 상태 변경
	if (KEYMANAGER->IsOnceKeyDown('S'))
	{
		searching = false;
		PLAYERMANAGER->EraseSearchVector();
		PLAYERMANAGER->EraseSearchBuildingVector();
		for (int i = 0; i < unitVector.size(); i++)
		{
			unitVector[i]->SetIsSearch(false);
			unitVector[i]->SetUnitState(IDLE);
		}
	}
	if (KEYMANAGER->IsOnceKeyDown('A'))	
	{
		searching = true;
		PLAYERMANAGER->EraseSearchVector();
		PLAYERMANAGER->EraseSearchBuildingVector();
		for (int i = 0; i < enemyUnitVector.size(); i++)
		{
			if (PtInRect(&enemyUnitVector[i]->GetUnitRect(), m_ptMouse))
			{
				PLAYERMANAGER->SetSearchEnemy(i);
				break;
			}
		}
		for (int i = 0; i < enemyBuildingVector.size(); i++)
		{
			if (PtInRect(&enemyBuildingVector[i]->GetBuildingRect(), m_ptMouse))
			{
				PLAYERMANAGER->SetSearchEnemyBuilding(i);
				break;
			}
		}
	}
	EFFECTMANAGER->Update();
}

void GameScene::Render()
{
	DrawTileMap();

	EFFECTMANAGER->Render();

	// 렉트 테스트용
	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		for (int i = 0; i < buildingVector.size(); i++)
		{
			Rectangle(GetMemDC(), buildingVector[i]->GetBuildingRect().left, buildingVector[i]->GetBuildingRect().top, buildingVector[i]->GetBuildingRect().right, buildingVector[i]->GetBuildingRect().bottom);
		}

		for (int i = 0; i < unitVector.size(); i++)
		{
			Rectangle(GetMemDC(), unitVector[i]->GetUnitRect().left, unitVector[i]->GetUnitRect().top, unitVector[i]->GetUnitRect().right, unitVector[i]->GetUnitRect().bottom);
		}

		for (int i = 0; i < airUnitVector.size(); i++)
		{
			Rectangle(GetMemDC(), airUnitVector[i]->GetUnitRect().left, airUnitVector[i]->GetUnitRect().top, airUnitVector[i]->GetUnitRect().right, airUnitVector[i]->GetUnitRect().bottom);
		}
	}

	// 지상 유닛 렌더링
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &unitVector[i]->GetUnitRect()))
		{
			unitVector[i]->Render(GetMemDC());
		}
	}
	
	for (int i = 0; i < enemyUnitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &enemyUnitVector[i]->GetUnitRect()))
		{
			enemyUnitVector[i]->Render(GetMemDC());
		}
	}

	for (int i = 0; i < enemyBuildingVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &enemyBuildingVector[i]->GetBuildingRect()))
		{
			enemyBuildingVector[i]->Render(GetMemDC());
		}
	}

	// 모든 건물 렌더링
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &buildingVector[i]->GetBuildingRect()))
		{
			buildingVector[i]->Render(GetMemDC());
		}
	}

	// 공중유닛 생산 렌더링
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetUnitKind() == LARVA)
		{
			unitVector[i]->RenderAirUint(GetMemDC());
		}
	}

	// 공중 유닛 그림자 렌더링
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &airUnitVector[i]->GetUnitRect()))
		{
			airUnitVector[i]->RenderShadow(GetMemDC());
		}
	}

	// 공중 유닛 렌더링
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (IntersectRect(&tempRect, &cameraRect2, &airUnitVector[i]->GetUnitRect()))
		{
			airUnitVector[i]->Render(GetMemDC());
		}
	}

	// 선택 드래그 렌더링
	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		HBRUSH myBrush, oldBrush;
		HPEN myPen, oldPen;

		myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(GetMemDC(), myBrush);
		myPen = CreatePen(PS_SOLID, 2, RGB(0, 222, 0));
		oldPen = (HPEN)SelectObject(GetMemDC(), myPen);

		//Rectangle(GetMemDC(), leftPoint, topPoint, rightPoint, bottomPoint);
		Rectangle(GetMemDC(), dragRect.left, dragRect.top, dragRect.right, dragRect.bottom);
		
		SelectObject(GetMemDC(), oldBrush);
		DeleteObject(myBrush);
		SelectObject(GetMemDC(), oldPen);
		DeleteObject(myPen);
	}
	else
	{
		dragRect.left = m_ptMouse.x;
		dragRect.top = m_ptMouse.y;
		dragRect.right = m_ptMouse.x;
		dragRect.bottom = m_ptMouse.y;
		//dragRect.left = CAMERAMANAGER->GetCameraCenter().x + WINSIZEX;
		//dragRect.top = CAMERAMANAGER->GetCameraCenter().y + WINSIZEY;
		//dragRect.right = CAMERAMANAGER->GetCameraCenter().x + WINSIZEX;
		//dragRect.bottom = CAMERAMANAGER->GetCameraCenter().y + WINSIZEY;
	}

	// 디버깅용 타일 그리기
	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		HBRUSH myBrush, oldBrush;
		HPEN myPen, oldPen;
		
		myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(GetMemDC(), myBrush);
		myPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(GetMemDC(), myPen);

		for (int i = 0; i < TILESIZE; i++)
		{
			if (IntersectRect(&tempRect, &cameraRect2, &_tileMap[i].rect))
			{
				Rectangle(GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].right, _tileMap[i].bottom);
			}
		}

		SelectObject(GetMemDC(), oldBrush);
		DeleteObject(myBrush);
		SelectObject(GetMemDC(), oldPen);
		DeleteObject(myPen);

	}

	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILESIZE; i++)
		{
			if (IntersectRect(&tempRect, &cameraRect2, &_tileMap[i].rect))
			{
				SetTextColor(GetMemDC(), RGB(255, 222, 222));
				sprintf_s(str, "(%d)", i);
				TextOut(GetMemDC(), _tileMap[i].left + CELL_WIDTH / 2 - 20, _tileMap[i].top + CELL_HEIGHT / 2 - 10, str, strlen(str));
			}
		}
	}

	// 유닛보다는 위에 있고 유닛 UI보다는 아래에 있는 콘솔 렌더링
	consoleImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	//Rectangle(GetMemDC(), commandRect.left, commandRect.top, commandRect.right, commandRect.bottom);
	
	HFONT myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "나눔고딕체");
	HFONT oldFont = (HFONT)SelectObject(GetMemDC(), myFont);

	// 콘솔 위에 띄워질 UI렌더링
	for (int i = 0; i < buildingVector.size(); i++)
	{
		if (buildingVector[i]->GetIsClick())
		{
			buildingVector[i]->RenderUI(GetMemDC());
			break;
		}
	}	
	for (int i = 0; i < enemyBuildingVector.size(); i++)
	{
		if (enemyBuildingVector[i]->GetIsClick())
		{
			enemyBuildingVector[i]->RenderUI(GetMemDC());
			break;
		}
	}
	for (int i = 0; i < unitVector.size(); i++)
	{
		if (unitVector[i]->GetIsClick())
		{
			unitVector[i]->RenderUI(GetMemDC());
			break;
		}
	}
	for (int i = 0; i < airUnitVector.size(); i++)
	{
		if (airUnitVector[i]->GetIsClick())
		{
			consoleImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);

			airUnitVector[i]->RenderUI(GetMemDC());
			break;
		}
	}
	
	SetTextColor(GetMemDC(), RGB(0, 222, 0));
	
	mineralImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	sprintf_s(str, "%.0f", mineral);
	TextOut(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + 35, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2 + 5, str, strlen(str));
	
	vespeneGasImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + WINSIZEX * 0.1, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	sprintf_s(str, "%.0f", vespeneGas);
	TextOut(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + WINSIZEX * 0.1 + 35, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2 + 5, str, strlen(str));
	
	populationImage->Render(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + WINSIZEX * 0.1 + WINSIZEX * 0.1, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2);
	sprintf_s(str, "%.0f/%.0f", currentPopulation, maxPopulation);
	TextOut(GetMemDC(), CAMERAMANAGER->GetCameraCenter().x + WINSIZEX * 0.2 + WINSIZEX * 0.1 + WINSIZEX * 0.1 + 35, CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2 + 5, str, strlen(str));

	SelectObject(GetMemDC(), oldFont);
	DeleteObject(myFont);
}

void GameScene::LoadMap(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TAGTILE) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}

void GameScene::DrawTileMap()
{
	for (int i = 0; i < TILESIZE; i++)
	{
		if (IntersectRect(&tempRect, &cameraRect1, &_tileMap[i].rect))
		{
			if (_tileMap[i].tileKind != TILEKIND_NONE)
			{
				switch (_tileMap[i].tileKind)
				{
				case TILEKIND_BASETERRAIN:
					IMAGEMANAGER->FrameRender("BaseMapCreep", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_TERRAIN:
					IMAGEMANAGER->FrameRender("MapTile1", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_CREEP:
					IMAGEMANAGER->FrameRender("MapTile1", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_STAIR:
					IMAGEMANAGER->FrameRender("MapTile2", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				case TILEKIND_STAIRBLOCK:
					IMAGEMANAGER->FrameRender("MapTile2", GetMemDC(), _tileMap[i].left, _tileMap[i].top, _tileMap[i].tilePos.x, _tileMap[i].tilePos.y);
					break;
				}
			}
		}
	}
}
