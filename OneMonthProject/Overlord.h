#pragma once
#include "UnitBase.h"

class Overlord : public UnitBase
{
public:
	Overlord();
	~Overlord();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

