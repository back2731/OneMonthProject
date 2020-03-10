#pragma once
#include "BuildBase.h"

class EvolutionChamber : public BuildBase
{
public:
	EvolutionChamber();
	~EvolutionChamber();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

