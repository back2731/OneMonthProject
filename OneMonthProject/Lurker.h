#pragma once
#include "UnitBase.h"

class Lurker : public UnitBase
{
public:
	Lurker();
	~Lurker();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

