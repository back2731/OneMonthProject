#pragma once
#include "BuildBase.h"

class DefilerMound : public BuildBase
{
public:
	DefilerMound();
	~DefilerMound();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

