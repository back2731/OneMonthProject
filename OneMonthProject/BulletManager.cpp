#include "stdafx.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

HRESULT BulletManager::Init()
{

	return S_OK;
}

void BulletManager::Release()
{
}

void BulletManager::Update()
{

}

void BulletManager::Render(HDC hdc)
{
}

void BulletManager::ShootBullet(string imageName, vector<BulletInfo>& bulletVector, float x, float y, float angle, float speed, float range, int count, int interval)
{
	// 카운트의 인터벌 모드 0이 될때마다 값을 조정해준다.
	if (count % interval == 0)
	{
		BulletInfo bullet;
		bullet = OBJECTPOOL->GetBullet();
		bullet.bulletImage = IMAGEMANAGER->FindImage(imageName);
		bullet.angle = angle;
		bullet.speed = speed;
		bullet.bulletX = bullet.unitX = x;
		bullet.bulletY = bullet.unitY = y;
		bullet.range = range;
		bullet.rect = RectMakeCenter(bullet.bulletX, bullet.bulletY, bullet.bulletImage->GetWidth(), bullet.bulletImage->GetHeight());
		bulletVector.push_back(bullet);
	}
}

void BulletManager::MovePlayerBullet(vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator & bulletIter)
{
	// 넣어둔 벡터의 이터레이터를 돌면서 값을 증가시켜 총알을 움직여준다.
	for (bulletIter = bulletVector.begin(); bulletIter != bulletVector.end();)
	{
		bulletIter->bulletX += cosf(bulletIter->angle) * bulletIter->speed;
		bulletIter->bulletY += -sinf(bulletIter->angle) * bulletIter->speed;

		bulletIter->rect = RectMakeCenter(bulletIter->bulletX, bulletIter->bulletY, bulletIter->bulletImage->GetWidth() - 13, bulletIter->bulletImage->GetHeight() - 13);
		//if (400 < GetDistance(bulletIter->x, bulletIter->y, bulletIter->fireX, bulletIter->fireY))
		//{
		//   bulletIter->y += 1;
		//}
		RECT temp;
		if (bulletIter->range < GetDistance(bulletIter->bulletX, bulletIter->bulletY, bulletIter->unitX, bulletIter->unitY))
		{
			OBJECTPOOL->SetBulletVector(bulletVector.front());
			EFFECTMANAGER->Play("tearpoof", bulletIter->rect.left, bulletIter->rect.top + 20);
			bulletIter = bulletVector.erase(bulletIter);
		}
		else
		{
			++bulletIter;
		}
	}
}

void BulletManager::MoveEnemyBullet(vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator & bulletIter)
{
	// 넣어둔 벡터의 이터레이터를 돌면서 값을 증가시켜 총알을 움직여준다.
	for (bulletIter = bulletVector.begin(); bulletIter != bulletVector.end();)
	{
		bulletIter->bulletX += cosf(bulletIter->angle) * bulletIter->speed;
		bulletIter->bulletY += -sinf(bulletIter->angle) * bulletIter->speed;

		bulletIter->rect = RectMakeCenter(bulletIter->bulletX, bulletIter->bulletY, bulletIter->bulletImage->GetWidth() - 13, bulletIter->bulletImage->GetHeight() - 13);
		//if (400 < GetDistance(bulletIter->x, bulletIter->y, bulletIter->fireX, bulletIter->fireY))
		//{
		//   bulletIter->y += 1;
		//}
		RECT temp;
		if (bulletIter->range < GetDistance(bulletIter->bulletX, bulletIter->bulletY, bulletIter->unitX, bulletIter->unitY))
		{
			OBJECTPOOL->SetBulletVector(bulletVector.front());
			EFFECTMANAGER->Play("enemyBloodpoof", bulletIter->rect.left, bulletIter->rect.top + 20);
			bulletIter = bulletVector.erase(bulletIter);
		}
		else
		{
			++bulletIter;
		}
	}
}

void BulletManager::RenderBullet(HDC hdc, vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator & bulletIter)
{
	//이터레이터를 돌면서 총알을 그려준다.
	bulletIter = bulletVector.begin();

	for (bulletIter; bulletIter != bulletVector.end(); ++bulletIter)
	{
		if (KEYMANAGER->IsToggleKey(VK_F2))
		{
			Rectangle(hdc, bulletIter->rect.left, bulletIter->rect.top, bulletIter->rect.right, bulletIter->rect.bottom);
		}

		bulletIter->bulletImage->Render(hdc, bulletIter->rect.left - 6, bulletIter->rect.top - 6);
	}
}
