#pragma once
#include "BuildBase.h"

class CreepColony : public BuildBase
{
public:
	CreepColony();
	~CreepColony();

	CreepColony(int _playerNumber, POINT buildXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
};

