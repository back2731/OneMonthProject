#pragma once
#include "SingletonBase.h"
class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	int saveX;
	int saveY;
	
	bool selectLarva;
	
	bool inputCommandTransDrone;

	bool inputCommandMove;

	vector<int>	blockTile;
	int blockTileNum;
	vector<UnitBase*> tempVector;
	UnitBase* tempUnitBase;

public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetSelectLarva(bool _isPush) { selectLarva = _isPush; }
	bool GetSelectLarvaValue() { return selectLarva; }

	// 명령 컨트롤
	void SetInputCommandTransDrone(bool _inputCommand) { inputCommandTransDrone = _inputCommand; }
	bool GetInputCommandTransDrone() { return inputCommandTransDrone; }

	void SetInputCommandMove(bool _inputCommand) { inputCommandMove = _inputCommand; }
	bool GetInputCommandMove() { return inputCommandMove; }


	void SetXY(int x, int y);
	int GetSaveX() { return saveX; }
	int GetSaveY() { return saveY; }

	vector<UnitBase*> GetTempVector() { return tempVector; }
	void GetUnitVector(UnitBase* unitClass) { tempVector.push_back(unitClass); }
	UnitBase* ReturnUnitVector();
	
	vector<int> GetBlockTileVector() { return blockTile; }
	void SetBlockTile(int num) { blockTile.push_back(num); }
	
	int ReturnBlockTile(int i);

};

