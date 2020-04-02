#pragma once
#include "SingletonBase.h"

class UpgradeManager : public SingletonBase<UpgradeManager>
{
private:
	// ������� è�� ���׷��̵�
	int meleeAttack;
	int missileAttack;
	int evolveCarapace;

	// �����ε� ���׷��̵�
	bool evolveVentralSacs;
	bool evolveAntennae;
	bool evolvePneumatizedCarapace;

public:
	UpgradeManager();
	~UpgradeManager();

	HRESULT Init();

	// ������� è�� ���׷��̵�
	int GetMeleeAttack() { return meleeAttack; }
	void SetMeleeAttack(int num) { meleeAttack = num; }
	int GetMissileAttack() { return missileAttack; }
	void SetMissileAttack(int num) { missileAttack = num; }
	int GetEvolveCarapace() { return evolveCarapace; }
	void SetEvolveCarapace(int num) { evolveCarapace = num; }

	// �����ε� ���׷��̵�
	bool GetEvolveVentralSacs() { return evolveVentralSacs; }
	void SetEvolveVentralSacs(bool isUpgraded) { evolveVentralSacs = isUpgraded; }

	bool GetEvolveAntennae() { return evolveAntennae; }
	void SetEvolveAntennae(bool isUpgraded) { evolveAntennae = isUpgraded; }
	
	bool GetEvolvePneumatizedCarapace() { return evolvePneumatizedCarapace; }
	void SetEvolvePneumatizedCarapace(bool isUpgraded) { evolvePneumatizedCarapace = isUpgraded; }

};

