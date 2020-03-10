#pragma once
#include "BuildBase.h"

class CreepColony : public BuildBase
{
public:
	CreepColony();
	~CreepColony();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

