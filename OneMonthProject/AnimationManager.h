#pragma once
#include"SingletonBase.h"

class AnimationManager :  public SingletonBase<AnimationManager>
{
private:

	typedef map<string, Animation*> arrAnimation;
	typedef map<string, Animation*>::iterator iterArrAnimation;

	arrAnimation _animation;

public:
	AnimationManager();
	~AnimationManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
	//처음부터 끝까지
	void AddDefAnimation(string animationKeyName, char* imageKeyName, int fps, bool reverse = false, bool loop = false);
	//배열에 담아서
	void AddAnimation(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, bool loop = false);
	//구간
	void AddAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps,bool reverse =  false, bool loop = false);


	void Start(string animationKeyName);
	void Stop(string animationKeyName);
	void Pause(string animationKeyName);
	void Resume(string animationKeyName);
	//찾아라
	Animation* FindAnimation(string animationKeyName);


	//삭제
	void DeleteAll();

	
};

