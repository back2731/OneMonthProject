#pragma once
#include "BuildBase.h"

class UltraliskCavern : public BuildBase
{
public:
	UltraliskCavern();
	~UltraliskCavern();

	UltraliskCavern(int _playerNumber, POINT buildXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
};

