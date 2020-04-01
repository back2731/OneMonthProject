#include "stdafx.h"
#include "BuildQueensNest.h"


BuildQueensNest::BuildQueensNest()
{
}


BuildQueensNest::~BuildQueensNest()
{
}

void BuildQueensNest::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateQueensNest(PLAYER1, { mutateX, mutateY }));
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 150);
	PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 100);
}

void BuildQueensNest::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
