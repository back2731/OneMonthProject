#include "stdafx.h"
#include "BuildSpire.h"


BuildSpire::BuildSpire()
{
}


BuildSpire::~BuildSpire()
{
}

void BuildSpire::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateSpire(PLAYER1, { mutateX, mutateY }));
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 200);
	PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 150);
}

void BuildSpire::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
