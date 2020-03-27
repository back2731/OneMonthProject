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
	UNITMANAGER->SetUnitVector(UNITMANAGER->CreateDrone(PLAYER1, { birthX ,birthY }));
}

void TransformDrone::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
