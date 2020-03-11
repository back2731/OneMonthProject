#pragma once

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
