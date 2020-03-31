#pragma once
#include "UnitBase.h"

class Zergling : public UnitBase
{
private:
	int conutTest;
public:
	Zergling();
	~Zergling();
	Zergling(int _playerNumber, POINT birthXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void RenderUI(HDC hdc) override;

	void PlayAnimation();
};
 
