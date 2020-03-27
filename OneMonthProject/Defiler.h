#pragma once
#include "UnitBase.h"

class Defiler : public UnitBase
{
public:
	Defiler();
	~Defiler();
	Defiler(int _playerNumber, POINT birthXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void RenderUI(HDC hdc) override;

	void PlayAnimation();
};

