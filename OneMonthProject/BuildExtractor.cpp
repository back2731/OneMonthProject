#include "stdafx.h"
#include "BuildExtractor.h"


BuildExtractor::BuildExtractor()
{
}


BuildExtractor::~BuildExtractor()
{
}

void BuildExtractor::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateExtractor(PLAYER1, { mutateX, mutateY }));
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 50);
}

void BuildExtractor::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
