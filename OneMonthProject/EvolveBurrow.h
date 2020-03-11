#pragma once
#include "CommandBase.h"

class EvolveBurrow : public CommandBase
{
public:
	EvolveBurrow();
	~EvolveBurrow();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

