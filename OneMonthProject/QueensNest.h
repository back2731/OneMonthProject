#pragma once
#include "BuildBase.h"

class QueensNest : public BuildBase
{
public:
	QueensNest();
	~QueensNest();

	QueensNest(int _playerNumber, POINT buildXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
};

