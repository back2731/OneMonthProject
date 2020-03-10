#pragma once
#include "BuildBase.h"

class SunkenColony : public BuildBase
{
public:
	SunkenColony();
	~SunkenColony();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

