#pragma once
#include "BuildBase.h"

class Spire : public BuildBase
{
public:
	Spire();
	~Spire();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

