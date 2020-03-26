#pragma once
#include "BuildBase.h"

class HydraliskDen : public BuildBase
{
public:
	HydraliskDen();
	~HydraliskDen();

	HydraliskDen(int _playerNumber, POINT buildXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
};

