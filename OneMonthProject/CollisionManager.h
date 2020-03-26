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

	// 같은 벡터의 에너미 충돌
	void CollisionSameVector(vector<UnitBase*>& unitVector);
	void CollisionUnitToBuilding(vector<UnitBase*>& unitVector, vector<BuildBase*>& buildingVector);

};
