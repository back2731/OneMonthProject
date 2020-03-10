#pragma once
#include "BuildBase.h"

class GreaterSpire : public BuildBase
{
public:
	GreaterSpire();
	~GreaterSpire();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

