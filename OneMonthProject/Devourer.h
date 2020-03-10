#pragma once
#include "UnitBase.h"

class Devourer : public UnitBase
{
public:
	Devourer();
	~Devourer();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

