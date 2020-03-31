#include "stdafx.h"
#include "TransformScourge.h"


TransformScourge::TransformScourge()
{
}


TransformScourge::~TransformScourge()
{
}

void TransformScourge::Update()
{
	UNITMANAGER->SetAirUnitVector(UNITMANAGER->CreateScourge(PLAYER1, { birthX - 10, birthY - 60 }));
	UNITMANAGER->SetAirUnitVector(UNITMANAGER->CreateScourge(PLAYER1, { birthX + 10, birthY - 60 }));
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 1.0f);
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 25.0f);
	PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 75.0f);
}

void TransformScourge::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
