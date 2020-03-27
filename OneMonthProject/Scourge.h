#pragma once
#include "UnitBase.h"

class Scourge : public UnitBase
{
public:
	Scourge();
	~Scourge();

	Scourge(int _playerNumber, POINT birthXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void RenderUI(HDC hdc) override;

	void RenderShadow(HDC hdc) override;

	void PlayAnimation();
};

