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

enum STATE
{
	STATE_NONE,
	STATE_OPEN,
	STATE_CLOSE,
	STATE_PATH
};

enum DIRECTION
{
	DIRECTION_UP,
	DIRECTION_LEFTUP,
	DIRECTION_LEFT,
	DIRECTION_RIGHTDOWN,
	DIRECTION_DOWN,
	DIRECTION_LEFTDOWN,
	DIRECTION_RIGHT,
	DIRECTION_RIGHTUP
};

enum UNITKIND
{
	LARVA,
	DRONE,
	ZERGLING
};

enum UNITSTATE
{
	IDLE,
	MOVE,
	ATTACK
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

	int			unitState;				// 유닛 상태

	Image*		unitImage;				// 유닛 이미지
	Image*		enemyUnitImage1;				// 유닛 이미지
	Animation*	unitAnimation;			// 유닛 애니메이션
	Image*		unitSelectImage;		// 유닛 선택 테두리 이미지
	Image*		unitFrontProgressImage;	// 유닛 체력바 (전면)
	Image*		unitBackProgressImage;	// 유닛 체력바 (후면)

	RECT		unitRect;				// 유닛 렉트
	RECT		unitSearchingRect;			// 유닛 어택 렉트
	float		unitRectX;				// 유닛 렉트 X
	float		unitRectY;				// 유닛 렉트 Y
	float		unitImageWidthHalf;		// 유닛 이미지 WidthHalf
	float		unitImageHeightHalf;	// 유닛 이미지 HeightHalf

	float		unitImageWidthQuarter;	// 유닛 이미지 WidthQuarter
	float		unitImageHeightQuarter;	// 유닛 이미지 HeightQuarter

	float		unitSelectImageWidth;	// 유닛 Select 이미지 Width
	float		unitSelectImageHeight;	// 유닛 Select 이미지 Height
	
	float		unitProgressWidth;		// 유닛 프로그래스 Width
	float		unitProgressHeight;		// 유닛 프로그래스 Height

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
	int				saveUnitPosition;
	int				currentTile;

	bool			isClick;
	bool			isTransform;

	CommandBase*	commandSlot[COMMANDMAX];
	Image*			commandImage[COMMANDMAX];
	RECT			commandRect[COMMANDMAX];

	// a스타용 변수들
	TAGTILE			_tileMap[TILE_COUNT_X * TILE_COUNT_Y];

	vector<int>		openList;
	vector<int>		closeList;
	vector<int>::iterator iter;

	vector<int>		saveRoad;
	vector<int>		blockTile;
	vector<int>		gasTile;

	int				startTile;
	int				endTile;
	int				unitCurrentTile;

	bool			isFind;
	bool			noPath;
	bool			startAstar;

	bool			isArrive;
	bool			isSearch;

	RECT			rc[6];

	RECT			playerRect;
	int				playerStart;
	RECT			testRect[TILESIZE];

	int				endX;
	int				endY;
	int				count;

	int				playerX;
	int				playerY;

	int				saveNumber = DIRECTION_RIGHTDOWN;

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

	void SetIsSearch(int _isSearch) { isSearch = _isSearch; }

	RECT GetUnitRect() { return unitStatus.unitRect; }
	RECT GetunitSearchingRect() { return unitStatus.unitSearchingRect; }
	
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
	void SetBlock();
	void SetEndTile();
	void SetEndTile(int num);
	void SetAstarVector();
	void SetStartTile();
	void SetStartTile(int num);
	void MoveUnit();
	int ChangeImageFrame();

	void PlayAstar();

	void LoadMap(int loadCount);

	void SetTileBlock(int num, bool test) { _tileMap[num].block = test; }

	// 공격 접근용 

	void SetEndTileATK(int num);
};

