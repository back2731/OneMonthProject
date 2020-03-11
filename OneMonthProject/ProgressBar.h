#pragma once
#include"SingletonBase.h"
class ProgressBar :public SingletonBase<ProgressBar>
{
private:

	RECT rectProgress;		// ü�¹� ��Ʈ
	int _x, _y;
	int _width;				//���α���(��༮���� ������)

	Image* progressBarFront;		//ü�¹� ���̹���
	Image* progressBarBack;		//ü�¹� ���̹���

public:
	ProgressBar();
	~ProgressBar();

	HRESULT Init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void Release();
	void Update();
	void Render(HDC hdc);
	void Render(HDC hdc, float destX, float destY);
	//������ ����
	void SetGauge(float currentGauge, float maxGauge);

	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }

	RECT GetRect() { return rectProgress; }
};

