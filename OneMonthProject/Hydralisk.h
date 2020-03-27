#pragma once
#include "UnitBase.h"

class Hydralisk : public UnitBase
{
public:
	Hydralisk();
	~Hydralisk();

	Hydralisk(int _playerNumber, POINT birthXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void RenderUI(HDC hdc) override;

	void PlayAnimation();
};

