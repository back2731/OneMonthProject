#pragma once
#include"SingletonBase.h"
class ProgressBar :public SingletonBase<ProgressBar>
{
private:

	RECT rectProgress;		// 체력바 렉트
	int _x, _y;
	int _width;				//가로길이(요녀석으로 조정함)

	Image* progressBarFront;		//체력바 앞이미지
	Image* progressBarBack;		//체력바 뒤이미지

public:
	ProgressBar();
	~ProgressBar();

	HRESULT Init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void Release();
	void Update();
	void Render(HDC hdc);
	void Render(HDC hdc, float destX, float destY);
	//게이지 셋팅
	void SetGauge(float currentGauge, float maxGauge);

	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }

	RECT GetRect() { return rectProgress; }
};

