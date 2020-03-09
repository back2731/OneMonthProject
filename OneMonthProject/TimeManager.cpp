#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

HRESULT TimeManager::Init()
{
	_timer = new Timer;
	_timer->Init();
	return S_OK;
}

void TimeManager::Release()
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
		_timer = nullptr;
	}
}

void TimeManager::Update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->Tick(lock);
	}
}

void TimeManager::Render(HDC hdc)
{
	char str[256];

	string strFrame;
	//배경모드
	SetBkMode(hdc, TRANSPARENT);
	//색상
	SetTextColor(hdc, RGB(255, 0, 0));
	//디버그 모드라면
#ifdef _DEBUG

	if (_timer != nullptr)
	{
		if (KEYMANAGER->IsToggleKey(VK_F3))
		{
			//FPS
			sprintf_s(str, "FPS :  %d", _timer->GetFrameRate());
			TextOut(hdc, 0, 0, str, strlen(str));

			//전체 경과 시간
			sprintf_s(str, "worldTime :  %f", _timer->GetWorldTime());
			TextOut(hdc, 0, 20, str, strlen(str));
			//한프레임당 경과시간
			sprintf_s(str, "ElapsedTime :  %f", _timer->GetElapsedTime());
			TextOut(hdc, 0, 40, str, strlen(str));
		}
	}

#else
	if (_timer != nullptr)
	{
		//FPS
		sprintf_s(str, "FPS :  %d", _timer->GetFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}

#endif // _DEBUG


}
