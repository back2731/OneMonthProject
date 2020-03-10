#pragma once
#include "UnitBase.h"

class Defiler : public UnitBase
{
public:
	Defiler();
	~Defiler();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

