#pragma once
//ũ��
#define CELL_WIDTH 64
#define CELL_HEIGHT 64

//�ʱ���ǥ
#define INIT_X -1768
#define INIT_Y -1144
//Ÿ�� ����
#define TILE_COUNT_X 64
#define TILE_COUNT_Y 64

//Ÿ�� �̹���
#define TILE_SIZE_X 16
#define TILE_SIZE_Y 17


#define TILE_MAX 1

enum TILEKIND
{
	TILEKIND_NONE,
	TILEKIND_TERRAIN,
	TILEKIND_TERRAIN2,
	TILEKIND_TERRAIN3
};

struct TagTile
{
	int left, top, right, bottom; // x, y ��(rect�� left, top)

	RECT rect;

	//int index; // ���ΰ�. tileNum, tileKind, tilePos ���� ���.

	//int tileNum[TILE_MAX]; // ����Ÿ�� �ε���(���õ� â) index�� �����ͼ� ����.
	TILEKIND tileKind; // ������Ʈ, Ÿ�� ����.
	POINT tilePos; // ����Ÿ�Ͽ��� ������༮(frameX, frameY)


	//int height; // ���ϼ��� Ŀ���� ����
};
