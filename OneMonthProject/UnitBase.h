#pragma once
#include "CommandBase.h"
#include "ProgressBar.h"

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LEFTUP,
	LEFTDOWN,
	RIGHTUP,
	RIGHTDOWN
};

enum UNITKIND
{
	LARVA,
	DRONE,
};

struct UnitStatus
{
	UNITKIND	unitKind;				// ���� ����

	int			playerNumber;			// �÷��̾� �ѹ�

	int			unitMaxHp;				// ���� �ִ� ü��
	int			unitCurrentHp;			// ���� ���� ü��
	int			unitAtk;				// ���� ���ݷ�
	int			unitDef;				// ���� ����
	int			unitTime;				// ���� ���� �ð�

	int			unitMineralPrice;		// ���� �̳׶� ����
	int			unitGasPrice;			// ���� ���� ����

	Image*		unitImage;				// ���� �̹���
	Image*		unitShadowImage;		// ���� �̹���
	Animation*	unitAnimation;			// ���� �ִϸ��̼�
	Image*		unitSelectImage;		// ���� ���� �׵θ� �̹���
	Image*		unitFrontProgress;		// ���� ü�¹� (����)
	Image*		unitBackProgress;		// ���� ü�¹� (�ĸ�)

	RECT		unitRect;				// ���� ��Ʈ
	float		unitRectX;				// ���� ��Ʈ X
	float		unitRectY;				// ���� ��Ʈ Y

	int			frameCount;				// �ִϸ��̼ǿ� ī��Ʈ ����
	int			frameIndexX;			// �ִϸ��̼ǿ� �ε��� ���� X
	int			frameIndexY;			// �ִϸ��̼ǿ� �ε��� ���� Y
};

class UnitBase
{
protected:
	UnitStatus		unitStatus;
	ProgressBar*	progressBar;
	
	int				direction;

	bool			isClick;
	bool			isTransform;

	CommandBase*	commandSlot[COMMANDMAX];
	RECT			commandRect[COMMANDMAX];

public:
	UnitBase();
	~UnitBase();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void RenderUI(HDC hdc);

	virtual int GetHatcheryX();
	virtual int GetHatcheryY();
	virtual int GetLarvaNumber();

	void PlayAnimation();

	RECT GetUnitRect() { return unitStatus.unitRect; }

	float GetUnitRectX() { return unitStatus.unitRectX; }
	float GetUnitRectY() { return unitStatus.unitRectY; }

	float GetUnitRectLeft() { return unitStatus.unitRect.left; }
	float GetUnitRectTop() { return unitStatus.unitRect.top; }
	float GetUnitRectRight() { return unitStatus.unitRect.right; }
	float GetUnitRectBottom() { return unitStatus.unitRect.bottom; }
	
	void SetUnitRectX(float num) { unitStatus.unitRectX = num; }
	void SetUnitRectY(float num) { unitStatus.unitRectY = num; }

	void SetUnitRectLeft(float num) { unitStatus.unitRect.left = num; }
	void SetUnitRectTop(float num) { unitStatus.unitRect.top = num; }
	void SetUnitRectRight(float num) { unitStatus.unitRect.right = num; }
	void SetUnitRectBottom(float num) { unitStatus.unitRect.bottom = num; }

	int GetUnitPlayerNumber() { return unitStatus.playerNumber; }

	void SetIsClick(bool _isClick) { isClick = _isClick; }
	bool GetIsClick() { return isClick; }
	bool GetIsTransform() { return isTransform; }

	void SetCommandSlot(int rectNumber, CommandBase* commandClass);
	void SetCommandRect();

	UNITKIND GetUnitKind() { return unitStatus.unitKind; }


};

