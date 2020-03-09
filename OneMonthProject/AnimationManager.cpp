#include "stdafx.h"
#include "AnimationManager.h"


AnimationManager::AnimationManager()
{
}


AnimationManager::~AnimationManager()
{
}

HRESULT AnimationManager::Init()
{
	return S_OK;
}

void AnimationManager::Release()
{
	DeleteAll();
}

void AnimationManager::Update()
{
	iterArrAnimation iter = _animation.begin();

	for (iter; iter != _animation.end(); ++iter)
	{
		if (!iter->second->IsPlay())continue;
		iter->second->FrameUpdate(TIMEMANAGER->GetElapsedTime()*1.0f);
	}
}

void AnimationManager::Render()
{
}

void AnimationManager::AddDefAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop)
{
	//이미지 및 애니메이션 초기화
	Image* img = IMAGEMANAGER->FindImage(imageKeyName);
	Animation* ani = new Animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetDefPlayFrame(reverse, loop);
	ani->SetFPS(fps);

	//이미지와 애니메이션을 초기화 후 맵에 추가한다.
	_animation.insert(make_pair(animationKeyName, ani));

}

void AnimationManager::AddAnimation(string animationKeyName, char * imageKeyName, int * playArr, int arrLen, int fps, bool loop)
{
	//이미지 및 애니메이션 초기화
	Image* img = IMAGEMANAGER->FindImage(imageKeyName);
	Animation* ani = new Animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetPlayFrame(playArr,arrLen, loop);
	ani->SetFPS(fps);

	//이미지와 애니메이션을 초기화 후 맵에 추가한다.
	_animation.insert(make_pair(animationKeyName, ani));
}

void AnimationManager::AddAnimation(string animationKeyName, char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	//이미지 및 애니메이션 초기화
	Image* img = IMAGEMANAGER->FindImage(imageKeyName);
	Animation* ani = new Animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetPlayFrame(start, end,reverse, loop);
	ani->SetFPS(fps);

	//이미지와 애니메이션을 초기화 후 맵에 추가한다.
	_animation.insert(make_pair(animationKeyName, ani));
}

void AnimationManager::Start(string animationKeyName)
{
	iterArrAnimation iter = _animation.find(animationKeyName);
	iter->second->Start();
}

void AnimationManager::Stop(string animationKeyName)
{
	iterArrAnimation iter = _animation.find(animationKeyName);
	iter->second->Stop();
}

void AnimationManager::Pause(string animationKeyName)
{
	iterArrAnimation iter = _animation.find(animationKeyName);
	iter->second->Pause();
}

void AnimationManager::Resume(string animationKeyName)
{
	iterArrAnimation iter = _animation.find(animationKeyName);
	iter->second->Resume();
}

Animation* AnimationManager::FindAnimation(string animationKeyName)
{
	iterArrAnimation iter = _animation.find(animationKeyName);

	if (iter != _animation.end())
	{
		return iter->second;
	}

	return nullptr;
}

void AnimationManager::DeleteAll()
{
	iterArrAnimation iter = _animation.begin();

	for (; iter != _animation.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _animation.erase(iter);
		}
		else
		{
			++iter;

		}
	}
}
