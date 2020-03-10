#pragma once
#include "UnitBase.h"

class Drone : public UnitBase
{
public:
	Drone();
	~Drone();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

