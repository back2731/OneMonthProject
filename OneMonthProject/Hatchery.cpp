#include "stdafx.h"
#include "Hatchery.h"


Hatchery::Hatchery()
{
}


Hatchery::~Hatchery()
{
}

Hatchery::Hatchery(int _playerNumber)
{
	buildStatus.playerNumber = _playerNumber;
	buildStatus.buildingHp = 300;
	buildStatus.buildTime = 6.0f;
}

HRESULT Hatchery::Init()
{
	return S_OK;
}

void Hatchery::Release()
{
}

void Hatchery::Update()
{
}

void Hatchery::Render(HDC hdc)
{
}
