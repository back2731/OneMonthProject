#include "stdafx.h"
#include "BuildHatchery.h"


BuildHatchery::BuildHatchery()
{
}


BuildHatchery::~BuildHatchery()
{
}

void BuildHatchery::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateHatchery(PLAYER1, { mutateX, mutateY }));
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 300);
}

void BuildHatchery::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
