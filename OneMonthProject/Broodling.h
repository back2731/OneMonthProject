#pragma once
#include "UnitBase.h"

class Broodling : public UnitBase
{
public:
	Broodling();
	~Broodling();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

