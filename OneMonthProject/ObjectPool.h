#pragma once
#include "SingletonBase.h"

// 총알 구조체 정보
struct BulletInfo
{
	Image* bulletImage;
	float angle;
	float speed;
	float bulletX, bulletY;
	float unitX, unitY;
	float range;
	RECT rect;
};

class ObjectPool : public SingletonBase<ObjectPool>
{
private:

	// 총알 구조체 벡터, 이터레이터
	vector<BulletInfo> vBulletRepository;
	vector<BulletInfo>::iterator viBulletRepository;

	// 테스트용 
	char str[128];

public:
	ObjectPool();
	~ObjectPool();

	void Init();
	void Render(HDC hdc);

	// 총알 정보 세팅 함수
	void SetBulletVector(BulletInfo vSpentBullet);

	// 다 쓴 총알을 가져오는 함수
	BulletInfo GetBullet();
	vector<BulletInfo>::iterator GetBulletVectorIterator() { return viBulletRepository; }
};

