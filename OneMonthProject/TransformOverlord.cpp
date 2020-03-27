#include "stdafx.h"
#include "TransformOverlord.h"


TransformOverlord::TransformOverlord()
{
}


TransformOverlord::~TransformOverlord()
{
}

void TransformOverlord::Update()
{
	UNITMANAGER->SetAirUnitVector(UNITMANAGER->CreateOverlord(PLAYER1, { birthX, birthY - 100 }));
}

void TransformOverlord::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
