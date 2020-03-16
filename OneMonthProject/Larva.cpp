#include "stdafx.h"
#include "Larva.h"


Larva::Larva()
{
}


Larva::~Larva()
{
}

Larva::Larva(int _playerNumber, POINT birthXY, int _hatcheryX, int _hatcheryY, int _larvaNumber)
{
	progressBar = new ProgressBar;
	unitStatus.unitKind = LARVA;

	hatcheryX = _hatcheryX;
	hatcheryY = _hatcheryY;
	larvaNumber = _larvaNumber;

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 25;
	unitStatus.unitCurrentHp = 8;
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
	unitStatus.frameIndexY = RND->GetInt(16);
	rndNum = RND->GetFromIntTo(20, 50);
	isClick = false;

	direction = RIGHTDOWN;

	progressBar->Init("images/UI/ZurgUnitProgressFront.bmp", "images/UI/ZurgUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);

	// 명령 슬롯 생성
	SetCommandSlot(SLOT1, new TransformDrone);
	SetCommandSlot(SLOT2, new TransformZergling);
	SetCommandSlot(SLOT3, new TransformOverlord);
	SetCommandSlot(SLOT4, new TransformHydralisk);
	SetCommandSlot(SLOT5, new TransformMutalisk);
	SetCommandSlot(SLOT6, new TransformScourge);
	SetCommandSlot(SLOT7, new TransformQueen);
	SetCommandSlot(SLOT8, new TransformUltralisk);
	SetCommandSlot(SLOT9, new TransformDefiler);
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

	// 슬롯 위치 카메라 반영
	SetCommandRect();

	//direction = RND->GetInt(100);
	//switch (direction)
	//{
	//case UP:
	//	unitStatus.unitRectY -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.top -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.bottom -= LARVAMOVEPOWER;
	//	break;
	//case DOWN:
	//	unitStatus.unitRectY += LARVAMOVEPOWER;
	//	unitStatus.unitRect.top += LARVAMOVEPOWER;
	//	unitStatus.unitRect.bottom += LARVAMOVEPOWER;
	//	break;
	//case LEFT:
	//	unitStatus.unitRectX -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.left -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.right -= LARVAMOVEPOWER;
	//	break;
	//case RIGHT:
	//	unitStatus.unitRectX += LARVAMOVEPOWER;
	//	unitStatus.unitRect.left += LARVAMOVEPOWER;
	//	unitStatus.unitRect.right += LARVAMOVEPOWER;
	//	break;
	//case LEFTUP:
	//	unitStatus.unitRectX -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.left -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.right -= LARVAMOVEPOWER;
	//	unitStatus.unitRectY -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.top -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.bottom -= LARVAMOVEPOWER;
	//	break;
	//case LEFTDOWN:
	//	unitStatus.unitRectX -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.left -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.right -= LARVAMOVEPOWER;
	//	unitStatus.unitRectY += LARVAMOVEPOWER;
	//	unitStatus.unitRect.top += LARVAMOVEPOWER;
	//	unitStatus.unitRect.bottom += LARVAMOVEPOWER;
	//	break;
	//case RIGHTUP:
	//	unitStatus.unitRectX += LARVAMOVEPOWER;
	//	unitStatus.unitRect.left += LARVAMOVEPOWER;
	//	unitStatus.unitRect.right += LARVAMOVEPOWER;
	//	unitStatus.unitRectY -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.top -= LARVAMOVEPOWER;
	//	unitStatus.unitRect.bottom -= LARVAMOVEPOWER;
	//	break;
	//case RIGHTDOWN:
	//	unitStatus.unitRectX += LARVAMOVEPOWER;
	//	unitStatus.unitRect.left += LARVAMOVEPOWER;
	//	unitStatus.unitRect.right += LARVAMOVEPOWER;
	//	unitStatus.unitRectY += LARVAMOVEPOWER;
	//	unitStatus.unitRect.top += LARVAMOVEPOWER;
	//	unitStatus.unitRect.bottom += LARVAMOVEPOWER;
	//	break;
	//default:
	//	break;
	//}
	if (isClick)
	{
		// 명령 컨트롤 업데이트
		if (PtInRect(&commandRect[SLOT1], m_ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				commandSlot[SLOT1]->GetBirthXY(unitStatus.unitRectX, unitStatus.unitRectY);
				commandSlot[SLOT1]->Update();
			}
		}

	}	progressBar->SetGauge(unitStatus.unitCurrentHp, unitStatus.unitMaxHp);
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

void Larva::RenderUI(HDC hdc)
{
	if (isClick)
	{
		//buildStatus.buildingWireFrame->Render(hdc, CAMERAMANAGER->GetCameraCenter().x - 260, CAMERAMANAGER->GetCameraCenter().y + 280);

		if (KEYMANAGER->IsToggleKey(VK_TAB))
		{
			for (int i = 0; i < COMMANDMAX; i++)
			{
				Rectangle(hdc, commandRect[i].left, commandRect[i].top, commandRect[i].right, commandRect[i].bottom);
			}
		}
		IMAGEMANAGER->FindImage("TransformDrone")->Render(hdc, commandRect[SLOT1].left, commandRect[SLOT1].top);
		IMAGEMANAGER->FindImage("TransformZergling")->Render(hdc, commandRect[SLOT2].left, commandRect[SLOT2].top);
		IMAGEMANAGER->FindImage("TransformOverlord")->Render(hdc, commandRect[SLOT3].left, commandRect[SLOT3].top);
		IMAGEMANAGER->FindImage("TransformHydralisk")->Render(hdc, commandRect[SLOT4].left, commandRect[SLOT4].top);
		IMAGEMANAGER->FindImage("TransformMutalisk")->Render(hdc, commandRect[SLOT5].left, commandRect[SLOT5].top);
		IMAGEMANAGER->FindImage("TransformScourge")->Render(hdc, commandRect[SLOT6].left, commandRect[SLOT6].top);
		IMAGEMANAGER->FindImage("TransformQueen")->Render(hdc, commandRect[SLOT7].left, commandRect[SLOT7].top);
		IMAGEMANAGER->FindImage("TransformUltralisk")->Render(hdc, commandRect[SLOT8].left, commandRect[SLOT8].top);
		IMAGEMANAGER->FindImage("TransformDefiler")->Render(hdc, commandRect[SLOT9].left, commandRect[SLOT9].top);
	}

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
			test++;
			if (test % rndNum == 0)
			{
				if (unitStatus.frameIndexY < unitStatus.unitImage->GetMaxFrameY())
				{
					unitStatus.frameIndexY++;
				}
				else if (unitStatus.frameIndexY >= unitStatus.unitImage->GetMaxFrameY())
				{
					unitStatus.frameIndexY = 0;
					unitStatus.frameIndexY++;
				}
			}
		}
		unitStatus.unitImage->SetFrameX(unitStatus.frameIndexX);
		unitStatus.frameIndexX++;
	}
}
