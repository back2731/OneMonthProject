#pragma once
#include "UnitBase.h"

class Guardian : public UnitBase
{
public:
	Guardian();
	~Guardian();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

