#include "stdafx.h"
#include "BuildEvolutionChamber.h"


BuildEvolutionChamber::BuildEvolutionChamber()
{
}


BuildEvolutionChamber::~BuildEvolutionChamber()
{
}

void BuildEvolutionChamber::Update()
{
	BUILDMANAGER->SetBuildingVector(BUILDMANAGER->CreateEvolutionChamber(PLAYER1, { mutateX, mutateY }));
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 75);
}

void BuildEvolutionChamber::GetBirthXY(int X, int Y)
{
	mutateX = X;
	mutateY = Y;
}
