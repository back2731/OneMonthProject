#include "stdafx.h"
#include "BuildCreepColony.h"


BuildCreepColony::BuildCreepColony()
{
}


BuildCreepColony::~BuildCreepColony()
{
}

void BuildCreepColony::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateCreepColony(PLAYER1, { mutateX, mutateY }));
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 75);
}

void BuildCreepColony::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
