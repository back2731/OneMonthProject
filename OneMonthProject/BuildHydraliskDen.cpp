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
}

void BuildHydraliskDen::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
