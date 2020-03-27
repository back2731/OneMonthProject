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
	bool inputCommandTransOverlord;
	bool inputCommandTransHydralisk;
	bool inputCommandTransMutalisk;
	bool inputCommandTransScourge;
	bool inputCommandTransQueen;
	bool inputCommandTransUltralisk;
	bool inputCommandTransDefiler;

	vector<UnitBase*> tempUnitVector;
	UnitBase* tempUnitBase;

	vector<UnitBase*> tempAirUnitVector;
	UnitBase* tempAirUnitBase;

public:
	UnitManager();
	~UnitManager();

	HRESULT			Init();
	void			Release();
	void			Update();
	void			Render(HDC hdc);

	Larva*			CreateLarva(int playerNumber, POINT XY, int _hatcheryX, int _hatcheryY, int _larvaNumber);
	Drone*			CreateDrone(int playerNumber, POINT XY);
	Zergling*		CreateZergling(int playerNumber, POINT XY);
	Overlord*		CreateOverlord(int playerNumber, POINT XY);
	Hydralisk*		CreateHydralisk(int playerNumber, POINT XY);
	Mutalisk*		CreateMutalisk(int playerNumber, POINT XY);
	Scourge*		CreateScourge(int playerNumber, POINT XY);
	Queen*			CreateQueen(int playerNumber, POINT XY);
	Ultralisk*		CreateUltralisk(int playerNumber, POINT XY);
	Defiler*		CreateDefiler(int playerNumber, POINT XY);
	
	void			SetSelectLarva(bool _isPush) { selectLarva = _isPush; }
	bool			GetSelectLarvaValue() { return selectLarva; }

	void			SetXY(int x, int y);
	int				GetSaveX() { return saveX; }
	int				GetSaveY() { return saveY; }

	// 드론 생산
	void			SetInputCommandTransDrone(bool _inputCommand) { inputCommandTransDrone = _inputCommand; }
	bool			GetInputCommandTransDrone() { return inputCommandTransDrone; }
	
	// 저글링 생산
	void			SetInputCommandTransZergling(bool _inputCommand) { inputCommandTransZergling = _inputCommand; }
	bool			GetInputCommandTransZergling() { return inputCommandTransZergling; }
	
	// 오버로드 생산
	void			SetInputCommandTransOverlord(bool _inputCommand) { inputCommandTransOverlord = _inputCommand; }
	bool			GetInputCommandTransOverlord() { return inputCommandTransOverlord; }

	// 히드라리스크 생산
	void			SetInputCommandTransHydralisk(bool _inputCommand) { inputCommandTransHydralisk = _inputCommand; }
	bool			GetInputCommandTransHydralisk() { return inputCommandTransHydralisk; }

	// 뮤탈리스크 생산
	void			SetInputCommandTransMutalisk(bool _inputCommand) { inputCommandTransMutalisk = _inputCommand; }
	bool			GetInputCommandTransMutalisk() { return inputCommandTransMutalisk; }

	// 스커지 생산
	void			SetInputCommandTransScourge(bool _inputCommand) { inputCommandTransScourge = _inputCommand; }
	bool			GetInputCommandTransScourge() { return inputCommandTransScourge; }
	
	// 퀸 생산
	void			SetInputCommandTransQueen(bool _inputCommand) { inputCommandTransQueen = _inputCommand; }
	bool			GetInputCommandTransQueen() { return inputCommandTransQueen; }

	// 울트라리스크 생산
	void			SetInputCommandTransUltralisk(bool _inputCommand) { inputCommandTransUltralisk = _inputCommand; }
	bool			GetInputCommandTransUltralisk() { return inputCommandTransUltralisk; }
	
	// 디파일러 생산
	void			SetInputCommandTransDefiler(bool _inputCommand) { inputCommandTransDefiler = _inputCommand; }
	bool			GetInputCommandTransDefiler() { return inputCommandTransDefiler; }

	// 생산한 유닛을 벡터에 넣어주는 함수들
	vector<UnitBase*> GetTempVector() { return tempUnitVector; }
	void SetUnitVector(UnitBase* unitClass) { tempUnitVector.push_back(unitClass); }
	UnitBase* ReturnUnitVector();

	// 생산한 유닛을 벡터에 넣어주는 함수들
	vector<UnitBase*> GetAirUnitVector() { return tempAirUnitVector; }
	void SetAirUnitVector(UnitBase* unitClass) { tempAirUnitVector.push_back(unitClass); }
	UnitBase* ReturnAirUnitVector();
};

