#pragma once
#include "SingletonBase.h"

// �Ѿ� ����ü ����
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

	// �Ѿ� ����ü ����, ���ͷ�����
	vector<BulletInfo> vBulletRepository;
	vector<BulletInfo>::iterator viBulletRepository;

	// �׽�Ʈ�� 
	char str[128];

public:
	ObjectPool();
	~ObjectPool();

	void Init();
	void Render(HDC hdc);

	// �Ѿ� ���� ���� �Լ�
	void SetBulletVector(BulletInfo vSpentBullet);

	// �� �� �Ѿ��� �������� �Լ�
	BulletInfo GetBullet();
	vector<BulletInfo>::iterator GetBulletVectorIterator() { return viBulletRepository; }
};

