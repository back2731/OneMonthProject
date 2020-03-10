#pragma once
#include "BuildBase.h"

class Hatchery : public BuildBase
{
public:
	Hatchery();
	~Hatchery();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

