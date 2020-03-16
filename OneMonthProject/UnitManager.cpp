#include "stdafx.h"
#include "UnitManager.h"


UnitManager::UnitManager()
{
}


UnitManager::~UnitManager()
{
}

HRESULT UnitManager::Init()
{

	return S_OK;
}

void UnitManager::Release()
{
}

void UnitManager::Update()
{

}

void UnitManager::Render(HDC hdc)
{

}

Larva * UnitManager::CreateLarva(POINT XY, int _hatcheryX, int _hatcheryY, int _larvaNumber)
{
	return new Larva(PLAYER1, XY, _hatcheryX, _hatcheryY, _larvaNumber);
}

Drone * UnitManager::CreateDrone(POINT XY)
{
	return new Drone(PLAYER1, XY);
}
