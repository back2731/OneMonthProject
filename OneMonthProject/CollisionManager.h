#pragma once
#include"SingletonBase.h"

class CollisionManager : public SingletonBase<CollisionManager>
{
private:

public:
	CollisionManager();
	~CollisionManager();

	HRESULT Init();
};
