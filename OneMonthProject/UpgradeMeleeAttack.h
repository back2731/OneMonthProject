#pragma once
#include "CommandBase.h"

class UpgradeMeleeAttack : public CommandBase
{
public:
	UpgradeMeleeAttack();
	~UpgradeMeleeAttack();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

