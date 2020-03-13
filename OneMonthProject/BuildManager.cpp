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

Hatchery* BuildManager::CreateHatchery(POINT XY)
{
	return new Hatchery(PLAYER1, XY);
}
