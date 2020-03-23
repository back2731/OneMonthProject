#pragma once
#include "CommandBase.h"
#include "ProgressBar.h"

enum BUILDKIND
{
	HATCHERY,
};

struct BuildStatus
{
	BUILDKIND	buidKind;					// �ǹ�����

	int			playerNumber;				// �÷��̾� �ѹ�

	int			buildingMaxHp;				// �ǹ� �ִ� ü��
	int			buildingCurrentHp;			// �ǹ� ���� ü��
	int			buildingAtk;				// �ǹ� ���ݷ�
	int			buildingDef;				// �ǹ� ����
	int			buildTime;					// ���� �ð�

	int			buildingMineralPrice;		// �ǹ� �̳׶� ����
	int			buildingGasPrice;			// �ǹ� ���� ����
	
	Image*		buildImage;					// �ǹ� �̹���
	Animation*	buildAnimation;				// �ǹ� �ִϸ��̼�
	Image*		buildingSelectImage;		// �ǹ� ���� �׵θ� �̹���
	Image*		buildingFrontProgressImage;	// �ǹ� ü�¹� (����)
	Image*		buildingBackProgressImage;	// �ǹ� ü�¹� (�ĸ�)
	Image*		buildingWireFrame;			// �ǹ� ���̾�������

	RECT		buildRect;					// �ǹ� ��Ʈ
	float		buildRectX;					// �ǹ� ��Ʈ X
	float		buildRectY;					// �ǹ� ��Ʈ Y

	float		buildingImageWidthHalf;		// �ǹ� �̹��� WidthHalf
	float		buildingImageHeightHalf;	// �ǹ� �̹��� HeightHalf

	float		buildingImageWidthQuarter;	// �ǹ� �̹��� WidthQuarter
	float		buildingImageHeightQuarter;	// �ǹ� �̹��� HeightQuarter

	float		buildingSelectImageWidth;	// �ǹ� Select �̹��� Width
	float		buildingSelectImageHeight;	// �ǹ� Select �̹��� Height

	float		buildingProgressWidth;		// �ǹ� ���α׷��� Width
	float		buildingProgressHeight;		// �ǹ� ���α׷��� Height

	int			frameCount;					// �ִϸ��̼ǿ� ī��Ʈ ����
	int			frameIndexX;				// �ִϸ��̼ǿ� �ε��� ���� X
	int			frameIndexY;				// �ִϸ��̼ǿ� �ε��� ���� Y
};

class BuildBase
{
protected:
	RECT			temp;
	BuildStatus		buildStatus;
	ProgressBar*	progressBar;

	bool			isClick;

	CommandBase*	commandSlot[COMMANDMAX];
	RECT			commandRect[COMMANDMAX];


	int currentLarva;

public:
	BuildBase();
	~BuildBase();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void RenderUI(HDC hdc);

	virtual int GetMaxLarva();
	virtual int GetCurrentLarva();
	virtual void SetCurrentLarva(int _currentLarva);

	void PlayAnimation();

	RECT GetBuildingRect() { return buildStatus.buildRect; }
	int GetBuildingRectX() { return buildStatus.buildRect.left + (buildStatus.buildRect.right - buildStatus.buildRect.left) / 2; }
	int GetBuildingRectY() { return buildStatus.buildRect.top + (buildStatus.buildRect.bottom - buildStatus.buildRect.top) / 2; }

	int GetBuildingPlayerNumber() { return buildStatus.playerNumber; }

	void SetIsClick(bool _isClick) { isClick = _isClick; }
	bool GetIsClick() { return isClick; }

	void SetCommandSlot(int rectNumber, CommandBase* commandClass);
	void SetCommandRect();

	BUILDKIND GetBuildKind() { return buildStatus.buidKind; }

};

