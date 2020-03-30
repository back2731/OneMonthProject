#include "stdafx.h"
#include "TransformHydralisk.h"


TransformHydralisk::TransformHydralisk()
{
}


TransformHydralisk::~TransformHydralisk()
{
}

void TransformHydralisk::Update()
{
	UNITMANAGER->SetUnitVector(UNITMANAGER->CreateHydralisk(PLAYER1, { birthX, birthY }));
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 1);
}

void TransformHydralisk::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
