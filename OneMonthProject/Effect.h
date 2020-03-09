#pragma once
#include "GameNode.h"
class Effect :  public GameNode
{

private:
	Image* _EffectImage;		//����Ʈ �̹���
	Animation* _EffectAni;		//����Ʈ �ִϸ��̼�

	int _x, _y;					//����Ʈ ��Ʈ�� ��ǥ
	float _elapsedTime;			//����Ʈ ����ð�(�ӵ�)
	bool _isRunning;			//������̳�?

public:
	Effect();
	~Effect();
	//����Ʈ �ʱ�ȭ(����Ʈ �̹���, ����Ʈ �������� ���α���, ���α��� FPS, ����Ʈ �ӵ�)
	HRESULT Init (Image* EffectImage, int frameW, int frameH, int FPS, float elapsedTime);
	void Release();
	void Update();
	void Render();

	//���� ���ϴ� ��ǥ�� ����Ʈ��Ʈ����
	void StartEffect(int x, int y);
	//����Ʈ ���߱�
	void StopEffect();
	//����Ʈ ��������� ���°� ��������
	bool GetIsRunning() { return _isRunning; }
};

