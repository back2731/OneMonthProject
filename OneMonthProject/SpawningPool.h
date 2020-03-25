#pragma once
#include "BuildBase.h"

class SpawningPool : public BuildBase
{
private:
	
public:
	SpawningPool();
	~SpawningPool();

	SpawningPool(int _playerNumber, POINT buildXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
};

