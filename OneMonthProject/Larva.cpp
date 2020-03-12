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
	/*
			int			playerNumber;			// 플레이어 넘버

		int			unitMaxHp;				// 유닛 최대 체력
		int			unitCurrentHp;			// 유닛 현재 체력
		int			unitAtk;				// 유닛 공격력
		int			unitDef;				// 유닛 방어력
		int			unitTime;				// 유닛 생산 시간

		int			unitMineralPrice;		// 유닛 미네랄 가격
		int			unitGasPrice;			// 유닛 가스 가격

		Image*		unitImage;				// 유닛 이미지
		Animation*	unitAnimation;			// 유닛 애니메이션
		Image*		unitSelectImage;		// 유닛 선택 테두리 이미지
		Image*		unitFrontProgress;		// 유닛 체력바 (전면)
		Image*		unitBackProgress;		// 유닛 체력바 (후면)

		RECT		unitRect;				// 유닛 렉트
		float		unitRectX;				// 유닛 렉트 X
		float		unitRectY;				// 유닛 렉트 Y
	*/

	unitStatus.playerNumber = _playerNumber;

	unitStatus.unitMaxHp = 25;
	unitStatus.unitCurrentHp = 25;
	unitStatus.unitAtk = 0;
	unitStatus.unitDef = 10;
	unitStatus.unitTime = 0;

	unitStatus.unitMineralPrice = 0;
	unitStatus.unitGasPrice = 0;

	unitStatus.unitImage = IMAGEMANAGER->FindImage("larva");
	unitStatus.unitAnimation = ANIMATIONMANAGER->FindAnimation("larvaAnimation");
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("4X3");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth(), unitStatus.unitImage->GetFrameHeight());
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) / 2;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) / 2;

	PROGRESSMANAGER->Init("images/UI/ZurgProgressFront.bmp", "images/UI/ZurgProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 107 * 2, 9 * 2);
	PROGRESSMANAGER->SetGauge(unitStatus.unitCurrentHp, unitStatus.unitMaxHp);



}

HRESULT Larva::Init()
{
	return E_NOTIMPL;
}

void Larva::Release()
{
}

void Larva::Update()
{
	ANIMATIONMANAGER->Resume("larvaAnimation");

}

void Larva::Render(HDC hdc)
{
	if (PtInRect(&unitStatus.unitRect, m_ptMouse))
	{
		if (KEYMANAGER->IsToggleKey(VK_LBUTTON))
		{
			unitStatus.unitSelectImage->Render
			(hdc, unitStatus.unitRectX - unitStatus.unitSelectImage->GetWidth() / 2, unitStatus.unitRectY - unitStatus.unitSelectImage->GetHeight() / 2);
			PROGRESSMANAGER->Render
			(hdc, unitStatus.unitRectX - IMAGEMANAGER->FindImage("ZurgProgressBack")->GetWidth() / 2, unitStatus.unitRect.bottom - 75);
		}
	}

	unitStatus.unitImage->AniRender(hdc, unitStatus.unitRect.left, unitStatus.unitRect.top, unitStatus.unitAnimation);
}
