#pragma once
#include "BuildBase.h"

class Extractor : public BuildBase
{
public:
	Extractor();
	~Extractor();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

