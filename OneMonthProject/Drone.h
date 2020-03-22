#pragma once
#include "UnitBase.h"
#include "Gathering.h"
#include "BaseBuilding.h"
#include "HighBuilding.h"

class Drone : public UnitBase
{
private:
	char str[128];
	bool test;

	int testNum;
public:
	Drone();
	~Drone();
	Drone(int _playerNumber, POINT birthXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void RenderUI(HDC hdc) override;

	void PlayAnimation();
};

