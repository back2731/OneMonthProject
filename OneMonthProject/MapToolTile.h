#pragma once

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


enum TILEKIND
{
	TILEKIND_NONE,
	TILEKIND_BASETERRAIN,
	TILEKIND_TERRAIN,
	TILEKIND_STAIR,
	TILEKIND_STAIRBLOCK,
	TILEKIND_CREEP
};

struct TAGTILE
{
	int left, top, right, bottom; // x, y ��(rect�� left, top)

	RECT rect;

	//int index; // ���ΰ�. tileNum, tileKind, tilePos ���� ���.

	//int tileNum[TILE_MAX]; // ����Ÿ�� �ε���(���õ� â) index�� �����ͼ� ����.
	TILEKIND tileKind; // ������Ʈ, Ÿ�� ����.
	POINT tilePos; // ����Ÿ�Ͽ��� ������༮(frameX, frameY)
	
	bool creep;

	bool block;

	int node;

	int showState;

	int f, g, h;
//	bool isBlock;

	//int height; // ���ϼ��� Ŀ���� ����
};
