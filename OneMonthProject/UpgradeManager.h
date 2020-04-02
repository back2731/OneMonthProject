#pragma once
#include "SingletonBase.h"

class UpgradeManager : public SingletonBase<UpgradeManager>
{
private:
	// 에볼루션 챔버 업그레이드
	int meleeAttack;
	int missileAttack;
	int evolveCarapace;

	// 오버로드 업그레이드
	bool evolveVentralSacs;
	bool evolveAntennae;
	bool evolvePneumatizedCarapace;

public:
	UpgradeManager();
	~UpgradeManager();

	HRESULT Init();

	// 에볼루션 챔버 업그레이드
	int GetMeleeAttack() { return meleeAttack; }
	void SetMeleeAttack(int num) { meleeAttack = num; }
	int GetMissileAttack() { return missileAttack; }
	void SetMissileAttack(int num) { missileAttack = num; }
	int GetEvolveCarapace() { return evolveCarapace; }
	void SetEvolveCarapace(int num) { evolveCarapace = num; }

	// 오버로드 업그레이드
	bool GetEvolveVentralSacs() { return evolveVentralSacs; }
	void SetEvolveVentralSacs(bool isUpgraded) { evolveVentralSacs = isUpgraded; }

	bool GetEvolveAntennae() { return evolveAntennae; }
	void SetEvolveAntennae(bool isUpgraded) { evolveAntennae = isUpgraded; }
	
	bool GetEvolvePneumatizedCarapace() { return evolvePneumatizedCarapace; }
	void SetEvolvePneumatizedCarapace(bool isUpgraded) { evolvePneumatizedCarapace = isUpgraded; }

};

