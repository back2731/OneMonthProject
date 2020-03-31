#pragma once
#include"SingletonBase.h"
#include "UnitBase.h"
#include "BuildBase.h"
#define KNOCKBACK 30
#define BUILDKNOCKBACK 10

class CollisionManager : public SingletonBase<CollisionManager>
{
private:
	RECT temp;

public:
	CollisionManager();
	~CollisionManager();

	HRESULT Init();

	// ���� ������ ���ʹ� �浹
	void CollisionSameVector(vector<UnitBase*>& unitVector, int knockBack, bool isCheck);
	void CollisionUnitToBuilding(vector<UnitBase*>& unitVector, vector<BuildBase*>& buildingVector);
	void CollisionUnitToUnit(vector<UnitBase*>& unitVector, vector<UnitBase*>& _unitVector);

};
