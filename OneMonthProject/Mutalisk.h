#pragma once
#include "UnitBase.h"

class Mutalisk : public UnitBase
{
public:
	Mutalisk();
	~Mutalisk();

	Mutalisk(int _playerNumber, POINT birthXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void RenderUI(HDC hdc) override;

	void RenderShadow(HDC hdc) override;

	void PlayAnimation();


};

