#pragma once
class Timer
{
private :

	bool		_isHardware;			//���� Ÿ�̸Ӹ� �����ϳ�
	float		_timeScale;				//�ð������
	float		_timeElapsed;			//�������Ӵ� �����
	__int64		_curTime;				//����ð�
	__int64		_lastTime;				//�������ð�
	__int64		_periodFrequency;	    //�ð��ֱ�

	unsigned long _frameRate;			//FPS
	unsigned long _FPSFrameCount;		//FPSī��Ʈ


	float _FPStimeElapsed;					//FPS������ �ð��� ����ð��� �����
	float _worldTime;					//��ü�ð� �����

public:
	Timer();
	~Timer();

	HRESULT Init();
	//����ð� ���
	void Tick(float lockFPS = 0.0f);
	//����FPS��������
	unsigned long GetFrameRate(char* str = nullptr)const;
	//�������Ӵ� ����ð�
	float GetElapsedTime()const { return _timeElapsed; }
	//��ü ����ð� ��������
	float GetWorldTime()const { return _worldTime; }



};

