#include "stdafx.h"
#include "TransformMutalisk.h"


TransformMutalisk::TransformMutalisk()
{
}


TransformMutalisk::~TransformMutalisk()
{
}

void TransformMutalisk::Update()
{
	UNITMANAGER->SetAirUnitVector(UNITMANAGER->CreateMutalisk(PLAYER1, { birthX, birthY - 60 }));
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 2.0f);
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 100.0f);
	PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 100.0f);
}

void TransformMutalisk::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
