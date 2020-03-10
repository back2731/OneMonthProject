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

class BuildManager : public SingletonBase<BuildManager>
{
private:

	vector<BuildBase*> buildVector;

public:
	BuildManager();
	~BuildManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

