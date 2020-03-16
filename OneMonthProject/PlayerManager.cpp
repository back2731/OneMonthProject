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
	if (selectLarva)
	{

	}
}

void PlayerManager::Render(HDC hdc)
{
}

void PlayerManager::SetXY(int x, int y)
{
	saveX = x;
	saveY = y;
}
