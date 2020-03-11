#pragma once
#include "SingletonBase.h"
#include "Timer.h"
class TimeManager :  public SingletonBase<TimeManager>
{
private:

	Timer * _timer;
public:
	TimeManager();
	~TimeManager();


	HRESULT Init();
	void Release();
	void Update(float lock = 0.0f);
	void Render(HDC hdc);

	float GetElapsedTime()const { return _timer->GetElapsedTime(); }
	float GetWorldTime()const { return _timer->GetWorldTime(); }

	unsigned long GetFPS()const { return  _timer->GetFrameRate(); }


};

