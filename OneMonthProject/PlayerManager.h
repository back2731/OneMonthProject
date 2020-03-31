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

	vector<int> searchEnemy;
	vector<int> searchEnemyBuilding;

	vector<int> searchPlayer;
	vector<int> searchPlayerBuilding;

	float		maxPopulation;
	float		currentPopulation;
	float		mineral;
	float		vespeneGas;

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

	void SetmaxPopulation(int num) { maxPopulation = num; }
	float GetmaxPopulation() { return maxPopulation; }

	void SetCurrentPopulation(int num) { currentPopulation = num; }
	float GetCurrentPopulation() { return currentPopulation; }

	void SetMineral(int num) { mineral = num; }
	float GetMineral() { return mineral; }

	void SetVespeneGas(int num) { vespeneGas = num; }
	float GetVespeneGas() { return vespeneGas; }

	void SetSearchEnemy(int num) { searchEnemy.push_back(num); }
	vector<int> GetSearchEnemy() { return searchEnemy; }
	int ReturnSearchedEnemyNumber() { return searchEnemy[0]; }
	void EraseSearchVector() { searchEnemy.clear(); }

	void SetSearchEnemyBuilding(int num) { searchEnemyBuilding.push_back(num); }
	vector<int> GetSearchEnemyBuilding() { return searchEnemyBuilding; }
	int ReturnSearchedEnemyBuildingNumber() { return searchEnemyBuilding[0]; }
	void EraseSearchBuildingVector() { searchEnemyBuilding.clear(); }

	void SetSearchPlayer(int num) { searchPlayer.push_back(num); }
	vector<int> GetSearchPlayer() { return searchPlayer; }
	int ReturnSearchedPlayerNumber() { return searchPlayer[0]; }
	void EraseSearchPlayerVector() { searchPlayer.clear(); }

	void SetSearchPlayerBuilding(int num) { searchPlayerBuilding.push_back(num); }
	vector<int> GetSearchPlayerBuilding() { return searchPlayerBuilding; }
	int ReturnSearchedPlayerBuildingNumber() { return searchPlayerBuilding[0]; }
	void EraseSearchPlayerBuildingVector() { searchPlayerBuilding.clear(); }
};

