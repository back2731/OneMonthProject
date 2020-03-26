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
}

void BuildDefilerMound::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
