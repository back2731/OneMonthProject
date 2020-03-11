#pragma once
#include "CommandBase.h"

class SelectLarva : public CommandBase
{
public:
	SelectLarva();
	~SelectLarva();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

