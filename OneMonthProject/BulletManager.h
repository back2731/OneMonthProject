#pragma once
#include "SingletonBase.h"

class BulletManager : public SingletonBase<BulletManager>
{
private:

public:
	BulletManager();
	~BulletManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	// 총알 이미지 이름, 총알을 담는 벡터, 플레이어&총알 x, y, 각도, 총알 속도, 총알 사정거리, 인터벌 돌리는 변수, 인터벌을 얼마나 줄것인지에 대한 변수
	void ShootBullet(string imageName, vector<BulletInfo>& bulletVector, float x, float y, float angle, float speed, float range, int count, int interval);

	// 총알을 담은 벡터와 이터레이터를 넣어준다.
	void MovePlayerBullet(vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator& bulletIter);
	void MoveEnemyBullet(vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator& bulletIter);

	void RenderBullet(HDC hdc, vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator& bulletIter);

};

