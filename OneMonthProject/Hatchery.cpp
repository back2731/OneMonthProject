#include "stdafx.h"
#include "Hatchery.h"


Hatchery::Hatchery()
{
}


Hatchery::~Hatchery()
{
}

Hatchery::Hatchery(int _playerNumber, POINT buildXY)
{

	/*
		int			playerNumber;			// �÷��̾� �ѹ�

		int			buildingHp;				// �ǹ� ü��
		int			buildingAtk;			// �ǹ� ���ݷ�
		int			buildingDef;			// �ǹ� ����
		int			buildTime;				// ���� �ð�

		int			buildingMineralPrice;	// �ǹ� �̳׶� ����
		int			buildingGasPrice;		// �ǹ� ���� ����

		Image*		buildImage;				// �ǹ� �̹���
		Animation*	buildAnimation;			// �ǹ� �ִϸ��̼�
		Image*		buildingSelectImage;	// �ǹ� ���� �׵θ� �̹���
		Image*		buildingFrontProgress;	// �ǹ� ü�¹� (����)
		Image*		buildingBackProgress;	// �ǹ� ü�¹� (�ĸ�)

		RECT		buildRect;				// �ǹ� ��Ʈ
		float		buildRectX;				// �ǹ� ��Ʈ X
		float		buildRectY;				// �ǹ� ��Ʈ Y
	*/
	buildStatus.playerNumber = _playerNumber;

	buildStatus.buildingMaxHp = 1250;
	buildStatus.buildingCurrentHp = 500;
	buildStatus.buildingAtk = 0;
	buildStatus.buildingDef = 1;
	buildStatus.buildTime = 120;

	buildStatus.buildingMineralPrice = 300;
	buildStatus.buildingGasPrice = 0;

	buildStatus.buildImage = IMAGEMANAGER->FindImage("Hatchery");
	buildStatus.buildAnimation = ANIMATIONMANAGER->FindAnimation("HatcheryAnimation");
	buildStatus.buildingSelectImage = IMAGEMANAGER->FindImage("4X3");

	buildStatus.buildRect = RectMakeCenter(buildXY.x, buildXY.y, buildStatus.buildImage->GetFrameWidth(), buildStatus.buildImage->GetFrameHeight());
	buildStatus.buildRectX = buildStatus.buildRect.left + (buildStatus.buildRect.right - buildStatus.buildRect.left) / 2;
	buildStatus.buildRectY = buildStatus.buildRect.top + (buildStatus.buildRect.bottom - buildStatus.buildRect.top) / 2;

	PROGRESSMANAGER->Init("images/UI/ZurgProgressFront.bmp", "images/UI/ZurgProgressBack.bmp", buildStatus.buildRect.left, buildStatus.buildRect.bottom, 107 * 2, 9 * 2);
	PROGRESSMANAGER->SetGauge(buildStatus.buildingCurrentHp, buildStatus.buildingMaxHp);
}

HRESULT Hatchery::Init()
{
	return S_OK;
}

void Hatchery::Release()
{
}

void Hatchery::Update()
{
	ANIMATIONMANAGER->Resume("HatcheryAnimation");	

}

void Hatchery::Render(HDC hdc)
{
	if (PtInRect(&buildStatus.buildRect, m_ptMouse))
	{
		if (KEYMANAGER->IsToggleKey(VK_LBUTTON))
		{
			buildStatus.buildingSelectImage->Render
			(hdc, buildStatus.buildRectX - buildStatus.buildingSelectImage->GetWidth() / 2, buildStatus.buildRectY - buildStatus.buildingSelectImage->GetHeight() / 2);
			PROGRESSMANAGER->Render
			(hdc, buildStatus.buildRectX - IMAGEMANAGER->FindImage("ZurgProgressBack")->GetWidth() / 2, buildStatus.buildRect.bottom - 75);
		}
	}

	buildStatus.buildImage->AniRender(hdc, buildStatus.buildRect.left, buildStatus.buildRect.top, buildStatus.buildAnimation);
}
