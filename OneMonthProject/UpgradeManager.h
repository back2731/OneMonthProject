#pragma once
#include "SingletonBase.h"

class UpgradeManager : public SingletonBase<UpgradeManager>
{
private:
	int meleeAttack;
	int missileAttack;
	int evolveCarapace;

public:
	UpgradeManager();
	~UpgradeManager();

	int GetMeleeAttack() { return meleeAttack; }
	void SetMeleeAttack(int num) { meleeAttack = num; }

	int GetMissileAttack() { return missileAttack; }
	void SetMissileAttack(int num) { missileAttack = num; }

	int GetEvolveCarapace() { return evolveCarapace; }
	void SetEvolveCarapace(int num) { evolveCarapace = num; }
};

