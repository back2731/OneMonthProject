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

HydraliskDen* BuildManager::CreateHydraliskDen(int playerNumber, POINT XY)
{
	return new HydraliskDen(playerNumber, XY);
}

EvolutionChamber* BuildManager::CreateEvolutionChamber(int playerNumber, POINT XY)
{
	return new EvolutionChamber(playerNumber, XY);
}

CreepColony* BuildManager::CreateCreepColony(int playerNumber, POINT XY)
{
	return new CreepColony(playerNumber, XY);
}

Extractor* BuildManager::CreateExtractor(int playerNumber, POINT XY)
{
	return new Extractor(playerNumber, XY);
}

Spire* BuildManager::CreateSpire(int playerNumber, POINT XY)
{
	return new Spire(playerNumber, XY);
}

QueensNest* BuildManager::CreateQueensNest(int playerNumber, POINT XY)
{
	return new QueensNest(playerNumber, XY);
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
