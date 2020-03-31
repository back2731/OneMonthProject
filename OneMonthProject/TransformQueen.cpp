#include "stdafx.h"
#include "TransformQueen.h"


TransformQueen::TransformQueen()
{
}


TransformQueen::~TransformQueen()
{
}

void TransformQueen::Update()
{
	UNITMANAGER->SetAirUnitVector(UNITMANAGER->CreateQueen(PLAYER1, { birthX, birthY - 100 }));
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 2.0f);
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 100.0f);
	PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 100.0f);
}

void TransformQueen::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}

