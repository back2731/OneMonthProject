#pragma once
#include "BuildBase.h"

class Spire : public BuildBase
{
public:
	Spire();
	~Spire();
	
	Spire(int _playerNumber, POINT buildXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
};

