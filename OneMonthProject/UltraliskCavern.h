#pragma once
#include "BuildBase.h"

class UltraliskCavern : public BuildBase
{
public:
	UltraliskCavern();
	~UltraliskCavern();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

