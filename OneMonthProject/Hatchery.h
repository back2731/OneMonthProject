#pragma once
#include "BuildBase.h"
#include "EvolveBurrow.h"
#include "LairRequires.h"
#include "SelectLarva.h"
#include "SetRallyPoint.h"

class Hatchery : public BuildBase
{
private:

	bool isTransLair;
	bool isTransHive;

	bool hatchery;
	bool lair;
	bool hive;

public:
	Hatchery();
	~Hatchery();

	Hatchery(int _playerNumber, POINT buildXY);
	
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
	
	int GetCurrentLarva() { return currentLarva; }
	void SetCurrentLarva(int _currentLarva) { currentLarva += _currentLarva; }

	void PlayTransformAnimation();
};

