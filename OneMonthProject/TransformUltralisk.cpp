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
}

void TransformUltralisk::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;

}
