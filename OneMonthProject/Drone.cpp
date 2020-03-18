#include "stdafx.h"
#include "Drone.h"


Drone::Drone()
{
}


Drone::~Drone()
{
}

Drone::Drone(int _playerNumber, POINT birthXY)
{
	progressBar = new ProgressBar;
	unitStatus.unitKind = DRONE;

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 40;
	unitStatus.unitCurrentHp = 40;
	unitStatus.unitAtk = 5;
	unitStatus.unitDef = 0;
	unitStatus.unitTime = 0;

	unitStatus.unitMineralPrice = 50;
	unitStatus.unitGasPrice = 0;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("drone");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("2X2");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth() /3, unitStatus.unitImage->GetFrameHeight()/3);
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) / 2;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) / 2;

	unitStatus.frameCount = 0;
	unitStatus.frameIndexY = 5;
	isClick = false;

	progressBar->Init("images/UI/ZurgUnitProgressFront.bmp", "images/UI/ZurgUnitProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 29 * 2, 9 * 2);

}

HRESULT Drone::Init()
{
	return S_OK;
}

void Drone::Release()
{
}

void Drone::Update()
{
	PlayAnimation();
	//if (isClick)
	//{
	//	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
	//	{
	//		if (GetAngle(unitStatus.unitRectX, unitStatus.unitRectY, m_ptMouse.x, m_ptMouse.y) > ANGLE_60 &&
	//			GetAngle(unitStatus.unitRectX, unitStatus.unitRectY, m_ptMouse.x, m_ptMouse.y) < ANGLE_120)
	//		{
	//			direction = UP;
	//		}
	//		else if (GetAngle(unitStatus.unitRectX, unitStatus.unitRectY, m_ptMouse.x, m_ptMouse.y) > -ANGLE_30 &&
	//			GetAngle(unitStatus.unitRectX, unitStatus.unitRectY, m_ptMouse.x, m_ptMouse.y) < ANGLE_60)
	//		{
	//			direction = LEFT;
	//		}
	//		else if (GetAngle(unitStatus.unitRectX, unitStatus.unitRectY, m_ptMouse.x, m_ptMouse.y) > -ANGLE_60 &&
	//			GetAngle(unitStatus.unitRectX, unitStatus.unitRectY, m_ptMouse.x, m_ptMouse.y) < -ANGLE_120)
	//		{
	//			direction = DOWN;
	//		}
	//		else if (GetAngle(unitStatus.unitRectX, unitStatus.unitRectY, m_ptMouse.x, m_ptMouse.y) > ANGLE_120 &&
	//			GetAngle(unitStatus.unitRectX, unitStatus.unitRectY, m_ptMouse.x, m_ptMouse.y) < -ANGLE_180)
	//		{
	//			direction = RIGHT;
	//		}


	//	}

	//	switch (direction)
	//	{
	//	case UP:
	//		unitStatus.unitRectY -= 1;
	//		unitStatus.unitRect.top -= 1;
	//		unitStatus.unitRect.bottom -= 1;
	//		break;
	//	case DOWN:
	//		unitStatus.unitRectY += 1;
	//		unitStatus.unitRect.top += 1;
	//		unitStatus.unitRect.bottom += 1;
	//		break;
	//	case RIGHT:
	//		unitStatus.unitRectX += 1;
	//		unitStatus.unitRect.left += 1;
	//		unitStatus.unitRect.right += 1;
	//		break;
	//	case LEFT:
	//		unitStatus.unitRectX -= 1;
	//		unitStatus.unitRect.left -= 1;
	//		unitStatus.unitRect.right -= 1;
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

void Drone::Render(HDC hdc)
{
	if (isClick)
	{
		unitStatus.unitSelectImage->Render
		(hdc, unitStatus.unitRectX - unitStatus.unitSelectImage->GetWidth() / 2, unitStatus.unitRectY - unitStatus.unitSelectImage->GetHeight() / 2);
		progressBar->Render
		(hdc, unitStatus.unitRectX - IMAGEMANAGER->FindImage("ZurgUnitProgressBack")->GetWidth() / 2, unitStatus.unitRect.bottom - 10);
	}
	unitStatus.unitImage->FrameRender(hdc, unitStatus.unitRectX - unitStatus.unitImage->GetFrameWidth() / 2, unitStatus.unitRectY - unitStatus.unitImage->GetFrameHeight() / 2, unitStatus.frameIndexX, unitStatus.frameIndexY);
	
	sprintf_s(str, "angle :  %f", GetAngle(unitStatus.unitRectX, unitStatus.unitRectY, m_ptMouse.x, m_ptMouse.y));
	TextOut(hdc, 0, 30, str, strlen(str));
}

void Drone::RenderUI(HDC hdc)
{

}

void Drone::PlayAnimation()
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
