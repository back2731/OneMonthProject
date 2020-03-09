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
	//ó������ ������
	void AddDefAnimation(string animationKeyName, char* imageKeyName, int fps, bool reverse = false, bool loop = false);
	//�迭�� ��Ƽ�
	void AddAnimation(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, bool loop = false);
	//����
	void AddAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps,bool reverse =  false, bool loop = false);


	void Start(string animationKeyName);
	void Stop(string animationKeyName);
	void Pause(string animationKeyName);
	void Resume(string animationKeyName);
	//ã�ƶ�
	Animation* FindAnimation(string animationKeyName);


	//����
	void DeleteAll();

	
};

