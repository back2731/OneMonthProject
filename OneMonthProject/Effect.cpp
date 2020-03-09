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

	//����Ʈ �̹����� ������ �ٷ� ����
	if (!EffectImage)return E_FAIL;
	_EffectImage = EffectImage;
	_elapsedTime = elapsedTime;
	_isRunning = false;
	//����Ʈ �ִϸ��̼��� ������ ���� ����!
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
	//����Ʈ �ִϸ��̼��� ���ᰡ �Ǹ� ������
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
	//��ġ ��ǥ�� ���� ��ǥ�� �����
	_x = x - (_EffectAni->GetFrameWidth() / 2);
	_y = y - (_EffectAni->GetFrameHeight() / 2);

	_isRunning = true;
	_EffectAni->Start();


}
void Effect::StopEffect()
{
	_isRunning = false;
}
