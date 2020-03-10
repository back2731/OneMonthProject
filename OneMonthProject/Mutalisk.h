#pragma once
#include "UnitBase.h"

class Mutalisk : public UnitBase
{
public:
	Mutalisk();
	~Mutalisk();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

