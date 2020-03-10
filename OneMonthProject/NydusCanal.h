#pragma once
#include "BuildBase.h"

class NydusCanal : public BuildBase
{
public:
	NydusCanal();
	~NydusCanal();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

