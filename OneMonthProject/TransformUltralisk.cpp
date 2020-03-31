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
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 4.0f);
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 200.0f);
	PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 200.0f);
}

void TransformUltralisk::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;

}
