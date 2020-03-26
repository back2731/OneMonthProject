#pragma once
#include "BuildBase.h"

class Extractor : public BuildBase
{
public:
	Extractor();
	~Extractor();

	Extractor(int _playerNumber, POINT buildXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
};

