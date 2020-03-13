#pragma once
#include "SingletonBase.h"
#include "Hatchery.h"
#include "CreepColony.h"
#include "SunkenColony.h"
#include "SporeColony.h"
#include "SpawningPool.h"
#include "EvolutionChamber.h"
#include "HydraliskDen.h"
#include "Lair.h"
#include "Spire.h"
#include "QueensNest.h"
#include "Hive.h"
#include "GreaterSpire.h"
#include "UltraliskCavern.h"
#include "DefilerMound.h"
#include "NydusCanal.h"
#include "InfestedCommand.h"

enum PlayerNumber
{
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	PLAYER5,
	PLAYER6,
	PLAYER7,
	PLAYER8
};
class BuildManager : public SingletonBase<BuildManager>
{
private:

public:
	BuildManager();
	~BuildManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	Hatchery* CreateHatchery(POINT XY);
};

