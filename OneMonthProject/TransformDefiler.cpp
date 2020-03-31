#include "stdafx.h"
#include "TransformDefiler.h"


TransformDefiler::TransformDefiler()
{
}


TransformDefiler::~TransformDefiler()
{
}

void TransformDefiler::Update()
{
	UNITMANAGER->SetUnitVector(UNITMANAGER->CreateDefiler(PLAYER1, { birthX, birthY }));
	PLAYERMANAGER->SetCurrentPopulation(PLAYERMANAGER->GetCurrentPopulation() + 2.0f);
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 50.0f);
	PLAYERMANAGER->SetVespeneGas(PLAYERMANAGER->GetVespeneGas() - 150.0f);
}

void TransformDefiler::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
