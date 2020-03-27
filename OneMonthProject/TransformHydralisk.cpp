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
}

void TransformHydralisk::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
