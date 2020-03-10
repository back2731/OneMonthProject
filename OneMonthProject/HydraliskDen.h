#pragma once
#include "BuildBase.h"

class HydraliskDen : public BuildBase
{
public:
	HydraliskDen();
	~HydraliskDen();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

