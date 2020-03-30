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
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 2);
}

void TransformQueen::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}

