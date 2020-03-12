#pragma once

struct UnitStatus
{
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
};
class UnitBase
{
protected:
	UnitStatus	unitStatus;

public:
	UnitBase();
	~UnitBase();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

