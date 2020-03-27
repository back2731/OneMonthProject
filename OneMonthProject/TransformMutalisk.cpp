#include "stdafx.h"
#include "TransformMutalisk.h"


TransformMutalisk::TransformMutalisk()
{
}


TransformMutalisk::~TransformMutalisk()
{
}

void TransformMutalisk::Update()
{
	UNITMANAGER->SetAirUnitVector(UNITMANAGER->CreateMutalisk(PLAYER1, { birthX, birthY - 60 }));
}

void TransformMutalisk::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
