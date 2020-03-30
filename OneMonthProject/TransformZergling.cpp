#include "stdafx.h"
#include "TransformZergling.h"


TransformZergling::TransformZergling()
{
}


TransformZergling::~TransformZergling()
{
}

void TransformZergling::Update()
{	
	UNITMANAGER->SetUnitVector(UNITMANAGER->CreateZergling(PLAYER1, { birthX - 20, birthY + 10 }));
	UNITMANAGER->SetUnitVector(UNITMANAGER->CreateZergling(PLAYER1, { birthX + 15, birthY - 10 }));
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 1);
}

void TransformZergling::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
