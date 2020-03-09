#pragma once
#include "SingletonBase.h"
#include "inc/fmod.hpp"
#pragma comment(lib,"lib/fmodex_vc.lib")
using namespace FMOD;

#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 100

#define TOTALSOUNDBUFFER SOUNDBUFFER+ EXTRACHANNELBUFFER
class SoundManager : public SingletonBase<SoundManager>
{
private:

	typedef map<string, Sound**>arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;


	System* m_system;		


	Sound** m_sound;		//사운드
	Channel** m_channel;		//채널


	arrSounds m_totalSounds;



public:
	SoundManager();
	~SoundManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
	//키값, 파일 이름, BGM, LOOP
	void AddSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);

	//사운드 플레이	(키값, 볼륨 0.0~1.0f)
	void Play(string keyName, float volume = 1.0f);

	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);

	//플레이 중이냐
	bool IsPlaySound(string keyName);
	//일시 정지 중이냐
	bool IsPauseSound(string keyName);


};

