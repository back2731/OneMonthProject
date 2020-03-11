#pragma once
#include "CommandBase.h"

class SetRallyPoint : public CommandBase
{
public:
	SetRallyPoint();
	~SetRallyPoint();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

