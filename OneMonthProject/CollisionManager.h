#pragma once
#include"SingletonBase.h"
#include "UnitBase.h"
#define KNOCKBACK 30

class CollisionManager : public SingletonBase<CollisionManager>
{
private:
	RECT temp;

public:
	CollisionManager();
	~CollisionManager();

	HRESULT Init();

	// 같은 벡터의 에너미 충돌
	void SameVectorCollision(vector<UnitBase*>& unitVector);

};
