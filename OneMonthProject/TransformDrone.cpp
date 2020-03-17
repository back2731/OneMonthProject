#include "stdafx.h"
#include "TransformDrone.h"


TransformDrone::TransformDrone()
{
}


TransformDrone::~TransformDrone()
{
}

void TransformDrone::Update()
{
	PLAYERMANAGER->GetUnitVector(UNITMANAGER->CreateDrone({ birthX ,birthY }));
}

void TransformDrone::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
