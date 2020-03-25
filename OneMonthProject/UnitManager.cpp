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
	selectLarva = false;
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

Larva * UnitManager::CreateLarva(int playerNumber, POINT XY, int _hatcheryX, int _hatcheryY, int _larvaNumber)
{
	return new Larva(playerNumber, XY, _hatcheryX, _hatcheryY, _larvaNumber);
}

Drone * UnitManager::CreateDrone(POINT XY)
{
	return new Drone(PLAYER1, XY);
}

Zergling * UnitManager::CreateZergling(POINT XY)
{
	return new Zergling(PLAYER1, XY);
}

void UnitManager::SetXY(int x, int y)
{
	saveX = x;
	saveY = y;
}

UnitBase * UnitManager::ReturnUnitVector()
{
	if (tempVector.size() > 0)
	{
		tempUnitBase = tempVector[0];
		tempVector.erase(tempVector.begin());
	}

	return tempUnitBase;
}
