#include "stdafx.h"
#include "ProgressBar.h"
ProgressBar::ProgressBar()
{
}


ProgressBar::~ProgressBar()
{
}

HRESULT ProgressBar::Init(char * frontImage, char * backImage, float x, float y, int width, int height)
{
	_x = x;
	_y = y;

	rectProgress = RectMake(x, y, width, height);

	progressBarFront = new Image;
	progressBarFront->Init(frontImage, x, y, width, height, true, RGB(255, 0, 255));

	progressBarBack = new Image;
	progressBarBack->Init(backImage, x, y, width, height, true, RGB(255, 0, 255));


	_width = progressBarFront->GetWidth();

	return S_OK;
}

void ProgressBar::Release()
{
	SAFE_DELETE(progressBarFront);
	SAFE_DELETE(progressBarBack);
}

void ProgressBar::Update()
{
	rectProgress = RectMakeCenter(_x + progressBarBack->GetWidth() / 2,
		_y + progressBarBack->GetHeight() / 2,
		progressBarBack->GetWidth(), progressBarBack->GetHeight());
}

void ProgressBar::Render(HDC hdc)
{
	progressBarBack->Render(hdc, rectProgress.left, _y, 0, 0, progressBarBack->GetWidth(), progressBarBack->GetHeight());

	progressBarFront->Render(hdc,rectProgress.left + 4, _y, 0, 0, _width, progressBarBack->GetHeight());

}
void ProgressBar::Render(HDC hdc, float destX, float destY)
{
	progressBarBack->Render(hdc, destX, destY, 0, 0, progressBarBack->GetWidth(), progressBarBack->GetHeight());

	progressBarFront->Render(hdc, destX, destY, 0, 0, _width, progressBarBack->GetHeight());

}
void ProgressBar::SetGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge)* progressBarBack->GetWidth();
}
