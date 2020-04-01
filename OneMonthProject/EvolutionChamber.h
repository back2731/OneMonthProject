#pragma once
#include "BuildBase.h"

class EvolutionChamber : public BuildBase
{
private:
	Image* meleeAttackDescription;
	Image* missileAttackDescription;
	Image* carapaceDescription;

public:
	EvolutionChamber();
	~EvolutionChamber();

	EvolutionChamber(int _playerNumber, POINT buildXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
};

