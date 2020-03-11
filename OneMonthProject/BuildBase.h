#pragma once
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

	RECT		buildRect;				// �ǹ� ��Ʈ
	float		buildRectX;				// �ǹ� ��Ʈ X
	float		buildRectY;				// �ǹ� ��Ʈ Y


};

class BuildBase
{
protected:
	BuildStatus		buildStatus;
		
	bool			isClick;

public:
	BuildBase();
	~BuildBase();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	RECT	GetBuildingRect() { return buildStatus.buildRect; }

	int GetBuildingPlayerNumber() { return buildStatus.playerNumber; }
};

