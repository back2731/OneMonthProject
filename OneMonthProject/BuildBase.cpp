#include "stdafx.h"
#include "BuildBase.h"

BuildBase::BuildBase()
{
}

BuildBase::~BuildBase()
{
}

HRESULT BuildBase::Init()
{
	return E_NOTIMPL;
}

void BuildBase::Release()
{
}

void BuildBase::Update()
{
}

void BuildBase::Render(HDC hdc)
{
}

void BuildBase::RenderUI(HDC hdc)
{
}

int BuildBase::GetMaxLarva()
{
	return 0;
}

int BuildBase::GetCurrentLarva()
{
	return 0;
}

void BuildBase::SetCurrentLarva(int _currentLarva)
{
}

void BuildBase::PlayAnimation()
{
	buildStatus.frameIndexY = 0;

	buildStatus.frameCount++;
	buildStatus.buildImage->SetFrameY(buildStatus.frameIndexY);
	if (buildStatus.frameCount % 10 == 0)
	{
		buildStatus.frameCount = 0;
		if (buildStatus.frameIndexX >= buildStatus.buildImage->GetMaxFrameX())
		{
			buildStatus.frameIndexX = 0;
		}
		buildStatus.buildImage->SetFrameX(buildStatus.frameIndexX);
		buildStatus.frameIndexX++;
	}
}

void BuildBase::SetCommandSlot(int rectNumber, CommandBase* commandClass)
{
	commandSlot[rectNumber] = commandClass;
}

void BuildBase::SetCommandRect()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			commandRect[i * 3 + j] = RectMake(CAMERAMANAGER->GetCameraCenter().x + 335 + (j * 85), CAMERAMANAGER->GetCameraCenter().y + 225 + (i * 75), 70, 70);
		}
	}
}
