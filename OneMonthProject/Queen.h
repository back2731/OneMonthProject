#pragma once
#include "UnitBase.h"

class Queen : public UnitBase
{
public:
	Queen();
	~Queen();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

