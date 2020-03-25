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
	bool selectLarva;

	int saveX;
	int saveY;

	bool inputCommandTransDrone;
	bool inputCommandTransZergling;

	vector<UnitBase*> tempVector;
	UnitBase* tempUnitBase;

public:
	UnitManager();
	~UnitManager();

	HRESULT			Init();
	void			Release();
	void			Update();
	void			Render(HDC hdc);

	Larva*			CreateLarva(int playerNumber, POINT XY, int _hatcheryX, int _hatcheryY, int _larvaNumber);
	Drone*			CreateDrone(POINT XY);
	Zergling*		CreateZergling(POINT XY);
	
	void			SetSelectLarva(bool _isPush) { selectLarva = _isPush; }
	bool			GetSelectLarvaValue() { return selectLarva; }

	void			SetXY(int x, int y);
	int				GetSaveX() { return saveX; }
	int				GetSaveY() { return saveY; }

	// 생산 컨트롤
	void			SetInputCommandTransDrone(bool _inputCommand) { inputCommandTransDrone = _inputCommand; }
	bool			GetInputCommandTransDrone() { return inputCommandTransDrone; }

	void			SetInputCommandTransZergling(bool _inputCommand) { inputCommandTransZergling = _inputCommand; }
	bool			GetInputCommandTransZergling() { return inputCommandTransZergling; }


	// 생산한 유닛을 벡터에 넣어주는 함수들
	vector<UnitBase*> GetTempVector() { return tempVector; }
	void SetUnitVector(UnitBase* unitClass) { tempVector.push_back(unitClass); }
	UnitBase* ReturnUnitVector();
};

