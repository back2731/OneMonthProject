#include "stdafx.h"
#include "TransformScourge.h"


TransformScourge::TransformScourge()
{
}


TransformScourge::~TransformScourge()
{
}

void TransformScourge::Update()
{
	UNITMANAGER->SetAirUnitVector(UNITMANAGER->CreateScourge(PLAYER1, { birthX - 10, birthY - 60 }));
	UNITMANAGER->SetAirUnitVector(UNITMANAGER->CreateScourge(PLAYER1, { birthX + 10, birthY - 60 }));
}

void TransformScourge::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
