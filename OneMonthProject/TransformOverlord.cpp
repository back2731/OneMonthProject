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
	PLAYERMANAGER->SetMineral(PLAYERMANAGER->GetMineral() - 100.0f);
}

void TransformOverlord::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
