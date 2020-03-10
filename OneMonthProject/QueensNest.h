#pragma once
#include "BuildBase.h"

class QueensNest : public BuildBase
{
public:
	QueensNest();
	~QueensNest();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

