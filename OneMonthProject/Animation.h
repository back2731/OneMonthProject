#pragma once
class Animation
{
private:

	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;			//������ �÷��� ���

	_vFrameList _frameList;					//��������ġ���
	_vPlayList _playList;					//�÷��� ���

	int _frameNum;							//������ ����
	int _frameWidth;
	int _frameHeight;

	bool _loop;
	bool _play;
	
	float _FrameUpdateSec;					//������ ������Ʈ
	float _elapsedSec;						//������ ����ð�
	DWORD _nowPlayIndex;					//���� �÷��� �ε���
public:
	Animation();
	~Animation();


	HRESULT Init(int totalW, int totalH, int frameW, int frameH);
	//ó������ ������ �ִϸ��̼� ����
	void SetDefPlayFrame(bool reverse = false, bool loop = false);
	//�迭�� ����� �ִ� �ֵ鸸
	void SetPlayFrame(int* playArr, int arrLen, bool loop = false);
	//���۰� �������� ���ؼ�
	void SetPlayFrame(int start, int end, bool reverse =  false, bool loop = false);

	//�ʴ� ���� Ƚ��
	void SetFPS(int framePerSec);

	//������ ������Ʈ Ÿ��
	void FrameUpdate(float elapsedTime);

	void Start();
	void Stop();
	void Pause();
	void Resume();

	inline bool IsPlay() { return _play; }
	inline POINT GetFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int GetFrameWidth() { return _frameWidth; }
	inline int GetFrameHeight() { return _frameHeight; }
};
