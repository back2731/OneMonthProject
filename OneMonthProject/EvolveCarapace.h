#pragma once
#include "CommandBase.h"

class EvolveCarapace : public CommandBase
{

public :
	EvolveCarapace();
	~EvolveCarapace();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

