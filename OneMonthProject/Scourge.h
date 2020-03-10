#pragma once
#include "UnitBase.h"

class Scourge : public UnitBase
{
public:
	Scourge();
	~Scourge();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

