#pragma once
#include "UnitBase.h"

class Larva : public UnitBase
{

public:
	Larva();
	~Larva();

	Larva(int _playerNumber, POINT birthXY);

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void PlayAnimation();

};

