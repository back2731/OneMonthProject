#include "stdafx.h"
#include "TransformUltralisk.h"


TransformUltralisk::TransformUltralisk()
{
}


TransformUltralisk::~TransformUltralisk()
{
}

void TransformUltralisk::Update()
{
	UNITMANAGER->SetUnitVector(UNITMANAGER->CreateUltralisk(PLAYER1, { birthX, birthY }));
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 4);
}

void TransformUltralisk::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;

}
