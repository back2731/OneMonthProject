#pragma once
#include "CommandBase.h"
#include "ProgressBar.h"
#include "MapToolTile.h"

#define SPEED 5
#define SPEED2 3

//ũ��
#define CELL_WIDTH	64
#define CELL_HEIGHT 64

//Ÿ�� ����
#define TILE_COUNT_X 64
#define TILE_COUNT_Y 64

//Ÿ�� �̹���
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
	UNITKIND	unitKind;				// ���� ����

	int			playerNumber;			// �÷��̾� �ѹ�

	int			unitMaxHp;				// ���� �ִ� ü��
	int			unitCurrentHp;			// ���� ���� ü��
	int			unitAtk;				// ���� ���ݷ�
	int			unitDef;				// ���� ����
	int			unitTime;				// ���� ���� �ð�

	int			unitMineralPrice;		// ���� �̳׶� ����
	int			unitGasPrice;			// ���� ���� ����

	int			unitState;				// ���� ����

	Image*		unitImage;				// ���� �̹���
	Image*		enemyUnitImage1;				// ���� �̹���
	Animation*	unitAnimation;			// ���� �ִϸ��̼�
	Image*		unitSelectImage;		// ���� ���� �׵θ� �̹���
	Image*		unitFrontProgressImage;	// ���� ü�¹� (����)
	Image*		unitBackProgressImage;	// ���� ü�¹� (�ĸ�)

	RECT		unitRect;				// ���� ��Ʈ
	RECT		unitSearchingRect;			// ���� ���� ��Ʈ
	float		unitRectX;				// ���� ��Ʈ X
	float		unitRectY;				// ���� ��Ʈ Y
	float		unitImageWidthHalf;		// ���� �̹��� WidthHalf
	float		unitImageHeightHalf;	// ���� �̹��� HeightHalf

	float		unitImageWidthQuarter;	// ���� �̹��� WidthQuarter
	float		unitImageHeightQuarter;	// ���� �̹��� HeightQuarter

	float		unitSelectImageWidth;	// ���� Select �̹��� Width
	float		unitSelectImageHeight;	// ���� Select �̹��� Height
	
	float		unitProgressWidth;		// ���� ���α׷��� Width
	float		unitProgressHeight;		// ���� ���α׷��� Height

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
	int				saveUnitPosition;
	int				currentTile;

	bool			isClick;
	bool			isTransform;

	CommandBase*	commandSlot[COMMANDMAX];
	Image*			commandImage[COMMANDMAX];
	RECT			commandRect[COMMANDMAX];

	// a��Ÿ�� ������
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

	// a ��Ÿ �Լ�

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

	// ���� ���ٿ� 

	void SetEndTileATK(int num);
};

