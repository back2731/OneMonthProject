#pragma once
#include"SingletonBase.h"
//이펙트 클래스 전방선언
class Effect;
class EffectManager :  public SingletonBase<EffectManager>
{

private:
	//이펙트 클래스 담은 녀석
	typedef vector<Effect*>vEffect;
	typedef vector<Effect*>::iterator viEffect;
	//이펙트 클래스가 담겨져 있는 벡터를 담은 녀석
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;
	//모든 이펙트를 관리할 녀석
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;

	//실제 모든 이펙트가 담겨져 있는 녀석
	vTotalEffect m_vTotalEffect;
public:
	EffectManager();
	~EffectManager();


	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//이펙트 추가(키값, 이미지 이름, 이미지 가로, 세로, 한프레임 가로, 세로, FPS, 속도, 버퍼갯수)
	void AddEffect(string EffectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer);

	void Play(string EffectKey, int x, int y);

};

