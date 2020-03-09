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
	viTotalEffect vIter;		//��� ����Ʈ ������ ����
	miEffect mIter;				//����ƮŬ���� ����ִ� �༮

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		//����Ʈ�� ��� �ִ� ��
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				//����Ʈ Ŭ������ ���� ����
				viEffect vArriter;

				for (vArriter = mIter->second.begin(); vArriter != mIter->second.end();)
				{
					//����Ʈ Ŭ���� ������
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
	vEffect vEffectBuffer; //����Ʈ ����
	mEffect mArrEffect;		//������ ���� ����Ʈ

							//�̹������� �̹����Ŵ����� ����� �Ǿ� �ִٸ�
	if (IMAGEMANAGER->FindImage(imageName))
	{
		img = IMAGEMANAGER->FindImage(imageName);
	}
	else
	{
		img = IMAGEMANAGER->AddImage(EffectKey, imageName, imageW, imageH, true, RGB(255, 0, 255));
	}

	//���� ũ�⸸ŭ ����Ʈ�� �Ҵ��� �ʱ�ȭ �ؼ� ���ͷ� �����.
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new Effect);
		vEffectBuffer[i]->Init(img, frameW, frameH, fps, elapsedTime);
	}

	//���� ��� ����Ʈ ���۸� �ʿ� �ִ´�.
	mArrEffect.insert(make_pair(EffectKey, vEffectBuffer));
	//�ʿ� ��� ���͸� ��Ż���Ϳ� ����.
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

			//����Ʈ Ű���� ���ؼ� ���� �ʴٸ� ���� ������ �ѱ���.
			if (!(mIter->first == EffectKey))break;


			//����Ʈ Ű���� ��ġ�ϸ� ����Ʈ�� �÷��� ����.
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
