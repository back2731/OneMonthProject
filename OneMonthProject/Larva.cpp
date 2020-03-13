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
			int			playerNumber;			// �÷��̾� �ѹ�

		int			unitMaxHp;				// ���� �ִ� ü��
		int			unitCurrentHp;			// ���� ���� ü��
		int			unitAtk;				// ���� ���ݷ�
		int			unitDef;				// ���� ����
		int			unitTime;				// ���� ���� �ð�

		int			unitMineralPrice;		// ���� �̳׶� ����
		int			unitGasPrice;			// ���� ���� ����

		Image*		unitImage;				// ���� �̹���
		Animation*	unitAnimation;			// ���� �ִϸ��̼�
		Image*		unitSelectImage;		// ���� ���� �׵θ� �̹���
		Image*		unitFrontProgress;		// ���� ü�¹� (����)
		Image*		unitBackProgress;		// ���� ü�¹� (�ĸ�)

		RECT		unitRect;				// ���� ��Ʈ
		float		unitRectX;				// ���� ��Ʈ X
		float		unitRectY;				// ���� ��Ʈ Y
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
	unitStatus.unitSelectImage = IMAGEMANAGER->FindImage("4X3");

	unitStatus.unitRect = RectMakeCenter(birthXY.x, birthXY.y, unitStatus.unitImage->GetFrameWidth(), unitStatus.unitImage->GetFrameHeight());
	unitStatus.unitRectX = unitStatus.unitRect.left + (unitStatus.unitRect.right - unitStatus.unitRect.left) / 2;
	unitStatus.unitRectY = unitStatus.unitRect.top + (unitStatus.unitRect.bottom - unitStatus.unitRect.top) / 2;

	unitStatus.frameCount = 0;
	unitStatus.frameIndexX = 0;
	unitStatus.frameIndexY = RND->GetInt(16);

	PROGRESSMANAGER->Init("images/UI/ZurgProgressFront.bmp", "images/UI/ZurgProgressBack.bmp", unitStatus.unitRect.left, unitStatus.unitRect.bottom, 107 * 2, 9 * 2);
	PROGRESSMANAGER->SetGauge(unitStatus.unitCurrentHp, unitStatus.unitMaxHp);
}

HRESULT Larva::Init()
{
	return S_OK;
}

void Larva::Release()
{
}

void Larva::Update()
{
	PlayAnimation();
}

void Larva::Render(HDC hdc)
{
	//if (PtInRect(&unitStatus.unitRect, m_ptMouse))
	//{
	//	if (KEYMANAGER->IsToggleKey(VK_LBUTTON))
	//	{
	//		unitStatus.unitSelectImage->Render
	//		(hdc, unitStatus.unitRectX - unitStatus.unitSelectImage->GetWidth() / 2, unitStatus.unitRectY - unitStatus.unitSelectImage->GetHeight() / 2);
	//		PROGRESSMANAGER->Render
	//		(hdc, unitStatus.unitRectX - IMAGEMANAGER->FindImage("ZurgProgressBack")->GetWidth() / 2, unitStatus.unitRect.bottom - 75);
	//	}
	//}

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
