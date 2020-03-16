#include "stdafx.h"
#include "UnitBase.h"

UnitBase::UnitBase()
{
}

UnitBase::~UnitBase()
{
}

HRESULT UnitBase::Init()
{
	return S_OK;
}

void UnitBase::Release()
{
}

void UnitBase::Update()
{
}

void UnitBase::Render(HDC hdc)
{
}

void UnitBase::RenderUI(HDC hdc)
{
}

int UnitBase::GetHatcheryX()
{
	return 0;
}

int UnitBase::GetHatcheryY()
{
	return 0;
}

int UnitBase::GetLarvaNumber()
{
	return 0;
}

void UnitBase::PlayAnimation()
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

void UnitBase::SetCommandSlot(int rectNumber, CommandBase* commandClass)
{
	commandSlot[rectNumber] = commandClass;
}

void UnitBase::SetCommandRect()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			commandRect[i * 3 + j] = RectMake(CAMERAMANAGER->GetCameraCenter().x + 335 + (j * 85), CAMERAMANAGER->GetCameraCenter().y + 225 + (i * 75), 70, 70);
		}
	}
}

