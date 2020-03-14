#pragma once
#include "BuildBase.h"

#define LARVAMAX 3

class Hatchery : public BuildBase
{
private:
	vector<UnitBase*> larvaVector;

	char str[128];

public:
	Hatchery();
	~Hatchery();

	Hatchery(int _playerNumber, POINT buildXY);


	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void PlayAnimation();
};

