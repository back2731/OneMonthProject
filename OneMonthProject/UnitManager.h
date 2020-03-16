#pragma once
#include "SingletonBase.h"
#include "Larva.h"
#include "Drone.h"
#include "Zergling.h"
#include "Overlord.h"
#include "Hydralisk.h"
#include "Lurker.h"
#include "Mutalisk.h"
#include "Guardian.h"
#include "Devourer.h"
#include "Scourge.h"
#include "Queen.h"
#include "Broodling.h"
#include "Ultralisk.h"
#include "Defiler.h"
#include "InfestedTerran.h"

class UnitManager : public SingletonBase<UnitManager>
{
private:

public:
	UnitManager();
	~UnitManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	Larva* CreateLarva(POINT XY, int _hatcheryX, int _hatcheryY, int _larvaNumber);
	Drone* CreateDrone(POINT XY);
};

