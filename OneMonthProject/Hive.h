#pragma once
#include "BuildBase.h"

class Hive : public BuildBase
{
public:
	Hive();
	~Hive();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

