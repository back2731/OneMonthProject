#include "stdafx.h"
#include "BuildHydraliskDen.h"


BuildHydraliskDen::BuildHydraliskDen()
{
}


BuildHydraliskDen::~BuildHydraliskDen()
{
}

void BuildHydraliskDen::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateHydraliskDen(PLAYER1, { mutateX, mutateY }));
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 100);
	PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 50);
}

void BuildHydraliskDen::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
