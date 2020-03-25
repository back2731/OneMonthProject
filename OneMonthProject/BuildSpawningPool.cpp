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
}

void BuildSpawningPool::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
