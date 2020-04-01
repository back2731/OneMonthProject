#include "stdafx.h"
#include "BuildSpawningPool.h"


BuildSpawningPool::BuildSpawningPool()
{
}


BuildSpawningPool::~BuildSpawningPool()
{
}

void BuildSpawningPool::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateSpawningPool(PLAYER1, { mutateX, mutateY }));
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 200);
}

void BuildSpawningPool::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
