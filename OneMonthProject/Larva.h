#pragma once
#include "UnitBase.h"

class Larva : public UnitBase
{
public:
	Larva();
	~Larva();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

