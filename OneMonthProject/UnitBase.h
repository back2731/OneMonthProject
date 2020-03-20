#pragma once
#include "CommandBase.h"
#include "ProgressBar.h"
#include "MapToolTile.h"

#define SPEED 5
#define SPEED2 3

//크기
#define CELL_WIDTH	64
#define CELL_HEIGHT 64

//타일 갯수
#define TILE_COUNT_X 64
#define TILE_COUNT_Y 64

//타일 이미지
#define TILE_SIZE_X 16
#define TILE_SIZE_Y 17

#define TILE_MAX 1

#define TILEX 64
#define TILEY 64
#define TILESIZE TILEX*TILEY

enum SELECT
{
	SELECT_START,
	SELECT_END,
	SELECT_BLOCK
};

struct TAGTILE
{
	RECT rc;
	bool block;

	int node;

	int showState;

	int f, g, h;
};

enum STATE
{
	STATE_NONE,
	STATE_OPEN,
	STATE_CLOSE,
	STATE_PATH
};


enum DIRECTION
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFTUP,
	DIRECTION_RIGHTDOWN,
	DIRECTION_LEFTDOWN,
	DIRECTION_RIGHTUP
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

	// a스타용 변수들
	TAGTILE			tiles[TILESIZE];
	TAGTILE			_tileMap[TILE_COUNT_X][TILE_COUNT_Y];

	vector<int>		openList;
	vector<int>		closeList;
	vector<int>::iterator iter;

	vector<int>		saveRoad;

	SELECT			currentSelect;

	int				startTile;
	int				endTile;
	int				currentTile;
	bool			isFind;
	bool			noPath;
	bool			startAstar;

	bool			isArrive;

	RECT			rc[6];

	RECT			playerRect;
	int				playerStart;
	RECT			testRect[TILESIZE];

	int				endX;
	int				endY;
	int				count;

	int				playerX;
	int				playerY;


	HBRUSH			brush;
	HFONT			font, oldFont;
	char			str[128];
	int				temp;
	const char*		fileName[10] = { "map1.map","map2.map","map3.map","map4.map","map5.map","map6.map","map7.map","map8.map","map9.map","map10.map" };

	HANDLE			file;
	DWORD			write;
	DWORD			read;

	int				currentX;
	int				currentY;

	RECT			cameraRect;
	RECT			tempRect;

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

	// a 스타 함수

	void InitAstar();
	void UpdateAstar(float unitX, float unitY);
	void RenderAstar(HDC hdc);

	void PlayAstar();

	void LoadMap(int loadCount);
};

