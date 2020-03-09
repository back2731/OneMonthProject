#include "stdafx.h"
#include "EffectManager.h"
#include "Effect.h"

EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
}

HRESULT EffectManager::Init()
{
	return S_OK;
}

void EffectManager::Release()
{
	viTotalEffect vIter;		//모든 이펙트 관리할 벡터
	miEffect mIter;				//이펙트클래스 담겨있는 녀석

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		//이펙트가 담겨 있는 맵
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				//이펙트 클래스를 담은 벡터
				viEffect vArriter;

				for (vArriter = mIter->second.begin(); vArriter != mIter->second.end();)
				{
					//이펙트 클래스 릴리즈
					(*vArriter)->Release();
					SAFE_DELETE(*vArriter);
					vArriter = mIter->second.erase(vArriter);
				}
			}
			else
			{
				++mIter;
			}
		}
	}
}

void EffectManager::Update()
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->Update();
			}
		}
	}

}

void EffectManager::Render()
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;

			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->Render();
			}
		}
	}
}

void EffectManager::AddEffect(string EffectKey, char * imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer)
{

	Image* img;
	vEffect vEffectBuffer; //이펙트 버퍼
	mEffect mArrEffect;		//맵으로 만든 이펙트

							//이미지가ㅏ 이미지매니저에 등록이 되어 있다면
	if (IMAGEMANAGER->FindImage(imageName))
	{
		img = IMAGEMANAGER->FindImage(imageName);
	}
	else
	{
		img = IMAGEMANAGER->AddImage(EffectKey, imageName, imageW, imageH, true, RGB(255, 0, 255));
	}

	//버퍼 크기만큼 이펙트를 할당후 초기화 해서 벡터로 만든다.
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new Effect);
		vEffectBuffer[i]->Init(img, frameW, frameH, fps, elapsedTime);
	}

	//벡터 담긴 이펙트 버퍼를 맵에 넣는다.
	mArrEffect.insert(make_pair(EffectKey, vEffectBuffer));
	//맵에 담긴 벡터를 토탈벡터에 담자.
	m_vTotalEffect.push_back(mArrEffect);


}

void EffectManager::Play(string EffectKey, int x, int y)
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{

			//이펙트 키값과 비교해서 같지 않다면 다음 맵으로 넘기자.
			if (!(mIter->first == EffectKey))break;


			//이펙트 키값과 일치하면 이펙트를 플레이 하자.
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->GetIsRunning())continue;
				(*vArrIter)->StartEffect(x, y);
				return;
			}
		}
	}
}
