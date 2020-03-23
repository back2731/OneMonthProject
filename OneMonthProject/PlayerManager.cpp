#include "stdafx.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

HRESULT PlayerManager::Init()
{
	selectLarva = false;
	return S_OK;
}

void PlayerManager::Release()
{
}

void PlayerManager::Update()
{

}

void PlayerManager::Render(HDC hdc)
{
}

void PlayerManager::SetXY(int x, int y)
{
	saveX = x;
	saveY = y;
}

UnitBase * PlayerManager::ReturnUnitVector()
{
	if (tempVector.size() > 0)
	{
		tempUnitBase = tempVector[0];
		tempVector.erase(tempVector.begin());
	}

	return tempUnitBase;
}

int PlayerManager::ReturnBlockTile(int i)
{
	blockTileNum = blockTile[i];
	return blockTileNum;
}
