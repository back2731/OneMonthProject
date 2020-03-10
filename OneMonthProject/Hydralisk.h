#pragma once
#include "UnitBase.h"

class Hydralisk : public UnitBase
{
public:
	Hydralisk();
	~Hydralisk();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

