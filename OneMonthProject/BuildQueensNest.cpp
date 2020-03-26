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
}

void BuildQueensNest::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
