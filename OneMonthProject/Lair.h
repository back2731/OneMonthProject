#pragma once
#include "BuildBase.h"

class Lair : public BuildBase
{
public:
	Lair();
	~Lair();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

