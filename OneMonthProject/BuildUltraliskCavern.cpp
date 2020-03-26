#include "stdafx.h"
#include "BuildUltraliskCavern.h"


BuildUltraliskCavern::BuildUltraliskCavern()
{
}


BuildUltraliskCavern::~BuildUltraliskCavern()
{
}

void BuildUltraliskCavern::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateUltraliskCavern(PLAYER1, { mutateX, mutateY }));
}

void BuildUltraliskCavern::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
