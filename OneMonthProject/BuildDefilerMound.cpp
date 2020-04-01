#include "stdafx.h"
#include "BuildDefilerMound.h"


BuildDefilerMound::BuildDefilerMound()
{
}


BuildDefilerMound::~BuildDefilerMound()
{
}

void BuildDefilerMound::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateDefilerMound(PLAYER1, { mutateX, mutateY }));
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 100);
	PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 100);
}

void BuildDefilerMound::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
