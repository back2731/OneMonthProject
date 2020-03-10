#pragma once
#include "UnitBase.h"

class Ultralisk : public UnitBase
{
public:
	Ultralisk();
	~Ultralisk();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

