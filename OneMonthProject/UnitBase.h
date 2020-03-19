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
	UNITKIND	unitKind;				// 유닛 종류

	int			playerNumber;			// 플레이어 넘버

	int			unitMaxHp;				// 유닛 최대 체력
	int			unitCurrentHp;			// 유닛 현재 체력
	int			unitAtk;				// 유닛 공격력
	int			unitDef;				// 유닛 방어력
	int			unitTime;				// 유닛 생산 시간

	int			unitMineralPrice;		// 유닛 미네랄 가격
	int			unitGasPrice;			// 유닛 가스 가격

	Image*		unitImage;				// 유닛 이미지
	Image*		unitShadowImage;		// 유닛 이미지
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

