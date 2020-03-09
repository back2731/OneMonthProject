#pragma once
#include"SingletonBase.h"
//����Ʈ Ŭ���� ���漱��
class Effect;
class EffectManager :  public SingletonBase<EffectManager>
{

private:
	//����Ʈ Ŭ���� ���� �༮
	typedef vector<Effect*>vEffect;
	typedef vector<Effect*>::iterator viEffect;
	//����Ʈ Ŭ������ ����� �ִ� ���͸� ���� �༮
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;
	//��� ����Ʈ�� ������ �༮
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;

	//���� ��� ����Ʈ�� ����� �ִ� �༮
	vTotalEffect m_vTotalEffect;
public:
	EffectManager();
	~EffectManager();


	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//����Ʈ �߰�(Ű��, �̹��� �̸�, �̹��� ����, ����, �������� ����, ����, FPS, �ӵ�, ���۰���)
	void AddEffect(string EffectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer);

	void Play(string EffectKey, int x, int y);

};

