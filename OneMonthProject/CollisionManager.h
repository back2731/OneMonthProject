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

	// ���� ������ ���ʹ� �浹
	void SameVectorCollision(vector<UnitBase*>& unitVector);

};
