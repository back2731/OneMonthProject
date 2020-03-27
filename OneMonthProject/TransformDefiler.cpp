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
}

void TransformDefiler::GetBirthXY(int X, int Y)
{
	birthX = X;
	birthY = Y;
}
