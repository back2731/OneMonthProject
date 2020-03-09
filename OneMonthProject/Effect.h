#pragma once
#include "GameNode.h"
class Effect :  public GameNode
{

private:
	Image* _EffectImage;		//이펙트 이미지
	Animation* _EffectAni;		//이펙트 애니메이션

	int _x, _y;					//이펙트 터트릴 좌표
	float _elapsedTime;			//이펙트 경과시간(속도)
	bool _isRunning;			//재생중이냐?

public:
	Effect();
	~Effect();
	//이펙트 초기화(이펙트 이미지, 이펙트 한프레임 가로길이, 세로길이 FPS, 이펙트 속도)
	HRESULT Init (Image* EffectImage, int frameW, int frameH, int FPS, float elapsedTime);
	void Release();
	void Update();
	void Render();

	//내가 원하는 좌표에 이펙트터트리기
	void StartEffect(int x, int y);
	//이펙트 멈추기
	void StopEffect();
	//이펙트 재생중인지 상태값 가져오기
	bool GetIsRunning() { return _isRunning; }
};

