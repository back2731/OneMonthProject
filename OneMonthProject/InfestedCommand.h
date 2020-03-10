#pragma once
#include "BuildBase.h"

class InfestedCommand : public BuildBase
{
public:
	InfestedCommand();
	~InfestedCommand();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

