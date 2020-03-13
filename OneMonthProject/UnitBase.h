#pragma once

struct UnitStatus
{
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

	int			frameCount;				// 애니메이션용 카운트 변수
	int			frameIndexX;			// 애니메이션용 인덱스 변수 X
	int			frameIndexY;			// 애니메이션용 인덱스 변수 Y
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

	virtual void PlayAnimation();

};

