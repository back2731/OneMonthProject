#pragma once
#include "CommandBase.h"

#define COMMANDMAX 9
#define COMMANDSLOTSIZE 64

struct BuildStatus
{
	int			playerNumber;			// �÷��̾� �ѹ�

	int			buildingMaxHp;			// �ǹ� �ִ� ü��
	int			buildingCurrentHp;		// �ǹ� ���� ü��
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
	Image*		buildingWireFrame;		// �ǹ� ���̾�������

	RECT		buildRect;				// �ǹ� ��Ʈ
	float		buildRectX;				// �ǹ� ��Ʈ X
	float		buildRectY;				// �ǹ� ��Ʈ Y

	int			frameCount;				// �ִϸ��̼ǿ� ī��Ʈ ����
	int			frameIndexX;			// �ִϸ��̼ǿ� �ε��� ���� X
	int			frameIndexY;			// �ִϸ��̼ǿ� �ε��� ���� Y
};

class BuildBase
{
protected:

	BuildStatus		buildStatus;
		
	bool			isClick;

	CommandBase*	commandSlot[COMMANDMAX];
	RECT			commandRect[COMMANDMAX];

public:
	BuildBase();
	~BuildBase();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void PlayAnimation();

	RECT GetBuildingRect() { return buildStatus.buildRect; }

	int GetBuildingPlayerNumber() { return buildStatus.playerNumber; }

	void SetIsClick(bool _isClick) { isClick = _isClick; }
	bool GetIsClick() { return isClick; }
};

