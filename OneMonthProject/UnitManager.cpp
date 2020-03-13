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

Larva * UnitManager::CreateLarva(POINT XY)
{
	return new Larva(PLAYER1, XY);
}
