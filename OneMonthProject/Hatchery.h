#pragma once
#include "BuildBase.h"

class Hatchery : public BuildBase
{
private:

public:
	Hatchery();
	~Hatchery();

	Hatchery(int _playerNumber, POINT buildXY);
	
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
	
	int GetCurrentLarva() { return currentLarva; }
	void SetCurrentLarva(int _currentLarva) { currentLarva += _currentLarva; }
};

