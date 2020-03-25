#include "stdafx.h"
#include "BuildManager.h"


BuildManager::BuildManager()
{
}


BuildManager::~BuildManager()
{
}

HRESULT BuildManager::Init()
{

	return S_OK;
}

void BuildManager::Release()
{

}

void BuildManager::Update()
{

}

void BuildManager::Render(HDC hdc)
{

}

Hatchery* BuildManager::CreateHatchery(int playerNumber, POINT XY)
{
	return new Hatchery(playerNumber, XY);
}

SpawningPool* BuildManager::CreateSpawningPool(int playerNumber, POINT XY)
{
	return new SpawningPool(playerNumber, XY);
}

BuildBase * BuildManager::ReturnBuildingVector()
{
	if (tempVector.size() > 0)
	{
		tempBuildBase = tempVector[0];
		tempVector.erase(tempVector.begin());
	}

	return tempBuildBase;
}
