#include "stdafx.h"
#include "UpgradeManager.h"


UpgradeManager::UpgradeManager()
{

}


UpgradeManager::~UpgradeManager()
{
}

HRESULT UpgradeManager::Init()
{
	meleeAttack = 0;
	missileAttack = 0;
	evolveCarapace = 0;

	evolveVentralSacs = false;
	evolveAntennae = false;
	evolvePneumatizedCarapace = false;

	return S_OK;
}

