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

	// ��� ����
	void			SetInputCommandTransDrone(bool _inputCommand) { inputCommandTransDrone = _inputCommand; }
	bool			GetInputCommandTransDrone() { return inputCommandTransDrone; }
	
	// ���۸� ����
	void			SetInputCommandTransZergling(bool _inputCommand) { inputCommandTransZergling = _inputCommand; }
	bool			GetInputCommandTransZergling() { return inputCommandTransZergling; }
	
	// �����ε� ����
	void			SetInputCommandTransOverlord(bool _inputCommand) { inputCommandTransOverlord = _inputCommand; }
	bool			GetInputCommandTransOverlord() { return inputCommandTransOverlord; }

	// ����󸮽�ũ ����
	void			SetInputCommandTransHydralisk(bool _inputCommand) { inputCommandTransHydralisk = _inputCommand; }
	bool			GetInputCommandTransHydralisk() { return inputCommandTransHydralisk; }

	// ��Ż����ũ ����
	void			SetInputCommandTransMutalisk(bool _inputCommand) { inputCommandTransMutalisk = _inputCommand; }
	bool			GetInputCommandTransMutalisk() { return inputCommandTransMutalisk; }

	// ��Ŀ�� ����
	void			SetInputCommandTransScourge(bool _inputCommand) { inputCommandTransScourge = _inputCommand; }
	bool			GetInputCommandTransScourge() { return inputCommandTransScourge; }
	
	// �� ����
	void			SetInputCommandTransQueen(bool _inputCommand) { inputCommandTransQueen = _inputCommand; }
	bool			GetInputCommandTransQueen() { return inputCommandTransQueen; }

	// ��Ʈ�󸮽�ũ ����
	void			SetInputCommandTransUltralisk(bool _inputCommand) { inputCommandTransUltralisk = _inputCommand; }
	bool			GetInputCommandTransUltralisk() { return inputCommandTransUltralisk; }
	
	// �����Ϸ� ����
	void			SetInputCommandTransDefiler(bool _inputCommand) { inputCommandTransDefiler = _inputCommand; }
	bool			GetInputCommandTransDefiler() { return inputCommandTransDefiler; }

	// ������ ������ ���Ϳ� �־��ִ� �Լ���
	vector<UnitBase*> GetTempVector() { return tempUnitVector; }
	void SetUnitVector(UnitBase* unitClass) { tempUnitVector.push_back(unitClass); }
	UnitBase* ReturnUnitVector();

	// ������ ������ ���Ϳ� �־��ִ� �Լ���
	vector<UnitBase*> GetAirUnitVector() { return tempAirUnitVector; }
	void SetAirUnitVector(UnitBase* unitClass) { tempAirUnitVector.push_back(unitClass); }
	UnitBase* ReturnAirUnitVector();
};

