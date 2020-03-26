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
}

void BuildSpire::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
