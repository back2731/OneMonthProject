#include "stdafx.h"
#include "Effect.h"
Effect::Effect()
	:_EffectImage(nullptr)
	,_EffectAni(nullptr)
	,_isRunning(NULL)
	,_x(0)
	,_y(0)
{
}
Effect::~Effect()
{
}
HRESULT Effect::Init (Image* EffectImage, int frameW, int frameH, int FPS, float elapsedTime)
{

	//이펙트 이미지가 없을때 바로 리턴
	if (!EffectImage)return E_FAIL;
	_EffectImage = EffectImage;
	_elapsedTime = elapsedTime;
	_isRunning = false;
	//이펙트 애니메이션이 없으면 새로 생성!
	if (!_EffectAni)_EffectAni = new Animation;

	_EffectAni->Init(_EffectImage->GetWidth(), _EffectImage->GetHeight(), frameW, frameH);
	_EffectAni->SetDefPlayFrame();
	_EffectAni->SetFPS(FPS);
	return S_OK;
}

void Effect::Release()
{
	SAFE_DELETE(_EffectAni);

}

void Effect::Update()
{
	if (_isRunning)
	{
		_EffectAni->FrameUpdate(_elapsedTime);
	}
	//이펙트 애니메이션이 종료가 되면 멈추자
	if (!_EffectAni->IsPlay())StopEffect();
}
void Effect::Render()
{
	if (_isRunning)
	{
		_EffectImage->AniRender(GetMemDC(), _x, _y, _EffectAni);
	}
}

void Effect::StartEffect(int x, int y)
{
	//위치 좌표를 센터 좌표로 만들기
	_x = x - (_EffectAni->GetFrameWidth() / 2);
	_y = y - (_EffectAni->GetFrameHeight() / 2);

	_isRunning = true;
	_EffectAni->Start();


}
void Effect::StopEffect()
{
	_isRunning = false;
}
