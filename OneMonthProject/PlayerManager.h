#pragma once
#include "SingletonBase.h"
class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	
	bool	inputCommandMove;
	bool	isSearch = false;

	int		changeState;
	int		saveUnitPosition;

	vector<int>	blockTile;
	int blockTileNum;

	vector<int>	gasTile;
	int gasTileNum;


public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	// 명령 컨트롤
	void SetInputCommandMove(bool _inputCommand) { inputCommandMove = _inputCommand; }
	bool GetInputCommandMove() { return inputCommandMove; }
	
	void SetChangeState(int _changeState) { changeState = _changeState; }
	int GetChangeState() { return changeState; }

	void SetSaveUnitPosition(int _saveUnitPosition) { saveUnitPosition = _saveUnitPosition; }
	int GetSaveUnitPosition() { return saveUnitPosition; }

	void SetIsSearch(int _isSearch) { isSearch = _isSearch; }
	int GetIsSearch() { return isSearch; }
		
	vector<int> GetBlockTileVector() { return blockTile; }
	void SetBlockTile(int num) { blockTile.push_back(num); }
	int ReturnBlockTile(int i);

	vector<int> GetGasTileVector() { return gasTile; }
	void SetGasTile(int num) { gasTile.push_back(num); }
	int ReturnGasTile(int i);

};

