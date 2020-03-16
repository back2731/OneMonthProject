#include "stdafx.h"
#include "TransformDrone.h"


TransformDrone::TransformDrone()
{
}


TransformDrone::~TransformDrone()
{
}

HRESULT TransformDrone::Init()
{
	return E_NOTIMPL;
}

void TransformDrone::Release()
{
}

void TransformDrone::Update()
{
	UNITMANAGER->CreateDrone({ birthX ,birthY });
}

void TransformDrone::Render(HDC hdc)
{
}

void TransformDrone::GetBirthXY(float X, float Y)
{
	birthX = X;
	birthY = Y;
}
