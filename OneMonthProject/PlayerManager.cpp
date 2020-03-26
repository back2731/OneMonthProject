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

int PlayerManager::ReturnBlockTile(int i)
{
	blockTileNum = blockTile[i];
	return blockTileNum;
}

int PlayerManager::ReturnGasTile(int i)
{
	gasTileNum = gasTile[i];
	return gasTileNum;
}
