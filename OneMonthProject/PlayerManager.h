#pragma once
#include "SingletonBase.h"
class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	int saveX;
	int saveY;
	
	bool selectLarva;
	bool inputCommand;

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

	void SetInputCommand(bool _inputCommand) { inputCommand = _inputCommand; }
	bool GetInputCommand() { return inputCommand; }

	void SetXY(int x, int y);
	int GetSaveX() { return saveX; }
	int GetSaveY() { return saveY; }

	vector<UnitBase*> GetTempVector() { return tempVector; }
	void GetUnitVector(UnitBase* unitClass) { tempVector.push_back(unitClass); }
	UnitBase* ReturnUnitVector();
};

