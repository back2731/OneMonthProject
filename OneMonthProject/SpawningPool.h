#pragma once
#include "BuildBase.h"

class SpawningPool : public BuildBase
{
public:
	SpawningPool();
	~SpawningPool();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

