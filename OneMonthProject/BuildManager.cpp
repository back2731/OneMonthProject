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
	//buildVector.push_back(new Hatchery(PLAYER1, PointMake(WINSIZEX/2, WINSIZEY/2)));
	//buildVector.push_back(new Hatchery(PLAYER2, PointMake(WINSIZEX/2+300, WINSIZEY/2)));
	//buildVector.push_back(new Hatchery(PLAYER2, PointMake(WINSIZEX/2-300, WINSIZEY/2)));
	//buildVector.push_back(new Hatchery(PLAYER2, PointMake(WINSIZEX/2, WINSIZEY/2+300)));
	//buildVector.push_back(new Hatchery(PLAYER2, PointMake(WINSIZEX/2, WINSIZEY/2-300)));
	//buildVector.push_back(new Hatchery(PLAYER2, PointMake(WINSIZEX/2+300, WINSIZEY/2+300)));
	//buildVector.push_back(new Hatchery(PLAYER2, PointMake(WINSIZEX/2+300, WINSIZEY/2-300)));
	//buildVector.push_back(new Hatchery(PLAYER2, PointMake(WINSIZEX/2-300, WINSIZEY/2-300)));
	//buildVector.push_back(new Hatchery(PLAYER2, PointMake(WINSIZEX/2-300, WINSIZEY/2+300)));
	test = false;
	return S_OK;
}

void BuildManager::Release()
{
	SAFE_DELETE(hatchery);
}

void BuildManager::Update()
{
	//for (int i = 0; i < buildVector.size(); i++)
	//{
	//	buildVector[i]->Update();
	//}
	if (test)
	{
		hatchery->Update();
	}
}

void BuildManager::Render(HDC hdc)
{
	if (test)
	{
		hatchery->Render(hdc);
	}
	//for (int i = 0; i < buildVector.size(); i++)
	//{
	//	if (buildVector[i]->GetBuildingPlayerNumber() == PLAYER1)
	//	{
	//		buildVector[i]->Render(hdc);
	//	}
	//}
}

Hatchery* BuildManager::CreateHatchery(POINT XY)
{
	return new Hatchery(PLAYER1, XY);
}
