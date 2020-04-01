#pragma once
#include "CommandBase.h"

class UpgradeMissileAttack : public CommandBase
{

public:
	UpgradeMissileAttack();
	~UpgradeMissileAttack();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

