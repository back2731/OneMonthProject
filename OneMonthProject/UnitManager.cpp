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
	unitVector.push_back(new Larva(PLAYER1, PointMake(WINSIZEX / 2, WINSIZEY / 2)));
	unitVector.push_back(new Larva(PLAYER1, PointMake(WINSIZEX / 2+36, WINSIZEY / 2)));
	unitVector.push_back(new Larva(PLAYER1, PointMake(WINSIZEX / 2-36, WINSIZEY / 2)));
	unitVector.push_back(new Larva(PLAYER1, PointMake(WINSIZEX / 2, WINSIZEY / 2+36)));
	unitVector.push_back(new Larva(PLAYER1, PointMake(WINSIZEX / 2, WINSIZEY / 2-36)));
	unitVector.push_back(new Larva(PLAYER1, PointMake(WINSIZEX / 2+36, WINSIZEY / 2+36)));
	unitVector.push_back(new Larva(PLAYER1, PointMake(WINSIZEX / 2+36, WINSIZEY / 2-36)));
	unitVector.push_back(new Larva(PLAYER1, PointMake(WINSIZEX / 2-36, WINSIZEY / 2-36)));
	unitVector.push_back(new Larva(PLAYER1, PointMake(WINSIZEX / 2-36, WINSIZEY / 2+36)));

	return S_OK;
}

void UnitManager::Release()
{
}

void UnitManager::Update()
{
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->Update();
	}
}

void UnitManager::Render(HDC hdc)
{
	for (int i = 0; i < unitVector.size(); i++)
	{
		unitVector[i]->Render(hdc);
	}

}
