#include "stdafx.h"
#include "Larva.h"


Larva::Larva()
{
}


Larva::~Larva()
{
}

Larva::Larva(int _playerNumber, POINT birthXY)
{
	progressBar = new ProgressBar;

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 25;
	unitStatus.unitCurrentHp =8;
	unitStatus.unitAtk = 0;
	unitStatus.unitDef = 10;
	unitStatus.unitTime = 0;

	unitStatus.unitMineralPrice = 0;
	unitStatus.unitGasPrice = 0;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("larva");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("1X1");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth(), unitStatus.unitImage->GetFrameHeight());
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) / 2;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) / 2;

	unitStatus.frameCount = 0;
	unitStatus.frameIndexX = 0;
	unitStatus.frameIndexY = RND->GetInt(16);

	isClick = false;
	progressBar->Init("images/UI/ZurgUnitProgressFront.bmp", "images/UI/ZurgUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);
}

HRESULT Larva::Init()
{
	return S_OK;
}

void Larva::Release()
{
	SAFE_DELETE(progressBar);
}

void Larva::Update()
{
	PlayAnimation();

	progressBar->SetGauge(unitStatus.unitCurrentHp, unitStatus.unitMaxHp);

}

void Larva::Render(HDC hdc)
{
	if (isClick)
	{
		unitStatus.unitSelectImage->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitSelectImage->GetWidth() / 2, unitStatus.unitRectY - unitStatus.unitSelectImage->GetHeight() / 2);
		progressBar->Render
		(hdc, unitStatus.unitRectX - IMAGEMANAGER->FindImage("ZurgUnitProgressBack")->GetWidth() / 2, unitStatus.unitRect.bottom-15);
	}
	unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRect.left, unitStatus.unitRect.top, unitStatus.frameIndexX, unitStatus.frameIndexY);
}

void Larva::PlayAnimation()
{
	unitStatus.frameCount++;
	unitStatus.unitImage->SetFrameY(unitStatus.frameIndexY);
	if (unitStatus.frameCount % 10 == 0)
	{
		unitStatus.frameCount = 0;
		if (unitStatus.frameIndexX >= unitStatus.unitImage->GetMaxFrameX())
		{
			unitStatus.frameIndexX = 0;
		}
		unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
		unitStatus.frameIndexX++;
	}
}
