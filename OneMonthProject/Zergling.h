#pragma once
#include "UnitBase.h"

class Zergling : public UnitBase
{
public:
	Zergling();
	~Zergling();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

