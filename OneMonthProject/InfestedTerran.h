#pragma once
#include "UnitBase.h"

class InfestedTerran : public UnitBase
{
public:
	InfestedTerran();
	~InfestedTerran();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

