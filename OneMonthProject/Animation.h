#pragma once
class Animation
{
private:

	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;			//프레임 플레이 목록

	_vFrameList _frameList;					//프레임위치목록
	_vPlayList _playList;					//플레이 목록

	int _frameNum;							//프레임 갯수
	int _frameWidth;
	int _frameHeight;

	bool _loop;
	bool _play;
	
	float _FrameUpdateSec;					//프레임 업데이트
	float _elapsedSec;						//프레임 경과시간
	DWORD _nowPlayIndex;					//현재 플레이 인덱스
public:
	Animation();
	~Animation();


	HRESULT Init(int totalW, int totalH, int frameW, int frameH);
	//처음부터 끝까지 애니메이션 셋팅
	void SetDefPlayFrame(bool reverse = false, bool loop = false);
	//배열에 담겨져 있는 애들만
	void SetPlayFrame(int* playArr, int arrLen, bool loop = false);
	//시작과 끝구간을 정해서
	void SetPlayFrame(int start, int end, bool reverse =  false, bool loop = false);

	//초당 갱신 횟수
	void SetFPS(int framePerSec);

	//프레임 업데이트 타임
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
