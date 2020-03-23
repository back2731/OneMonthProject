#pragma once
#include "CommandBase.h"
#include "ProgressBar.h"

enum BUILDKIND
{
	HATCHERY,
};

struct BuildStatus
{
	BUILDKIND	buidKind;					// 건물종류

	int			playerNumber;				// 플레이어 넘버

	int			buildingMaxHp;				// 건물 최대 체력
	int			buildingCurrentHp;			// 건물 현재 체력
	int			buildingAtk;				// 건물 공격력
	int			buildingDef;				// 건물 방어력
	int			buildTime;					// 빌드 시간

	int			buildingMineralPrice;		// 건물 미네랄 가격
	int			buildingGasPrice;			// 건물 가스 가격
	
	Image*		buildImage;					// 건물 이미지
	Animation*	buildAnimation;				// 건물 애니메이션
	Image*		buildingSelectImage;		// 건물 선택 테두리 이미지
	Image*		buildingFrontProgressImage;	// 건물 체력바 (전면)
	Image*		buildingBackProgressImage;	// 건물 체력바 (후면)
	Image*		buildingWireFrame;			// 건물 와이어프레임

	RECT		buildRect;					// 건물 렉트
	float		buildRectX;					// 건물 렉트 X
	float		buildRectY;					// 건물 렉트 Y

	float		buildingImageWidthHalf;		// 건물 이미지 WidthHalf
	float		buildingImageHeightHalf;	// 건물 이미지 HeightHalf

	float		buildingImageWidthQuarter;	// 건물 이미지 WidthQuarter
	float		buildingImageHeightQuarter;	// 건물 이미지 HeightQuarter

	float		buildingSelectImageWidth;	// 건물 Select 이미지 Width
	float		buildingSelectImageHeight;	// 건물 Select 이미지 Height

	float		buildingProgressWidth;		// 건물 프로그래스 Width
	float		buildingProgressHeight;		// 건물 프로그래스 Height

	int			frameCount;					// 애니메이션용 카운트 변수
	int			frameIndexX;				// 애니메이션용 인덱스 변수 X
	int			frameIndexY;				// 애니메이션용 인덱스 변수 Y
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

