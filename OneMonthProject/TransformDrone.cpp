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
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 1.0f);
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 50.0f);
}

void TransformDrone::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}

void TransformDrone::PayCost()
{
}
