#pragma once

enum TILEKIND
{
	TILEKIND_NONE,
	TILEKIND_TERRAIN,
	TILEKIND_TERRAIN2,
	TILEKIND_TERRAIN3
};

struct TAGTILE
{
	int left, top, right, bottom; // x, y 값(rect의 left, top)

	RECT rect;

	//int index; // 색인값. tileNum, tileKind, tilePos 에서 사용.

	//int tileNum[TILE_MAX]; // 샘플타일 인덱스(선택된 창) index를 가져와서 담음.
	TILEKIND tileKind; // 오브젝트, 타일 구분.
	POINT tilePos; // 샘플타일에서 골라진녀석(frameX, frameY)
	
	bool block;

	int node;

	int showState;

	int f, g, h;
//	bool isBlock;

	//int height; // 쌓일수록 커지는 높이
};
