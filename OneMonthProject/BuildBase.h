#pragma once
struct BuildStatus
{
	int			playerNumber;			// 플레이어 넘버

	int			buildingMaxHp;			// 건물 최대 체력
	int			buildingCurrentHp;		// 건물 현재 체력
	int			buildingAtk;			// 건물 공격력
	int			buildingDef;			// 건물 방어력
	int			buildTime;				// 빌드 시간

	int			buildingMineralPrice;	// 건물 미네랄 가격
	int			buildingGasPrice;		// 건물 가스 가격
	
	Image*		buildImage;				// 건물 이미지
	Animation*	buildAnimation;			// 건물 애니메이션
	Image*		buildingSelectImage;	// 건물 선택 테두리 이미지
	Image*		buildingFrontProgress;	// 건물 체력바 (전면)
	Image*		buildingBackProgress;	// 건물 체력바 (후면)

	RECT		buildRect;				// 건물 렉트
	float		buildRectX;				// 건물 렉트 X
	float		buildRectY;				// 건물 렉트 Y


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

