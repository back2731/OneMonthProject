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

Drone* UnitManager::CreateDrone(int playerNumber, POINT XY)
{
	return new Drone(playerNumber, XY);
}

Zergling* UnitManager::CreateZergling(int playerNumber, POINT XY)
{
	return new Zergling(playerNumber, XY);
}

Overlord* UnitManager::CreateOverlord(int playerNumber, POINT XY)
{
	return new Overlord(playerNumber, XY);
}

Hydralisk* UnitManager::CreateHydralisk(int playerNumber, POINT XY)
{
	return new Hydralisk(playerNumber, XY);
}

Mutalisk* UnitManager::CreateMutalisk(int playerNumber, POINT XY)
{
	return new Mutalisk(playerNumber, XY);
}

Scourge* UnitManager::CreateScourge(int playerNumber, POINT XY)
{
	return new Scourge(playerNumber, XY);
}

Queen* UnitManager::CreateQueen(int playerNumber, POINT XY)
{
	return new Queen(playerNumber, XY);
}

Ultralisk* UnitManager::CreateUltralisk(int playerNumber, POINT XY)
{
	return new Ultralisk(playerNumber, XY);
}

Defiler* UnitManager::CreateDefiler(int playerNumber, POINT XY)
{
	return new Defiler(playerNumber, XY);
}

void UnitManager::SetXY(int x, int y)
{
	saveX = x;
	saveY = y;
}

UnitBase * UnitManager::ReturnUnitVector()
{
	if (tempUnitVector.size() > 0)
	{
		tempUnitBase = tempUnitVector[0];
		tempUnitVector.erase(tempUnitVector.begin());
	}

	return tempUnitBase;
}

UnitBase * UnitManager::ReturnAirUnitVector()
{
	if (tempAirUnitVector.size() > 0)
	{
		tempAirUnitBase = tempAirUnitVector[0];
		tempAirUnitVector.erase(tempAirUnitVector.begin());
	}

	return tempAirUnitBase;
}
