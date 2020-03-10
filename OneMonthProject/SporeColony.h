#pragma once
#include "BuildBase.h"

class SporeColony : public BuildBase
{
public:
	SporeColony();
	~SporeColony();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

