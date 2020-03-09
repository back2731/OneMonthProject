#pragma once
//크기
#define CELL_WIDTH 64
#define CELL_HEIGHT 64

//초기좌표
#define INIT_X -1768
#define INIT_Y -1144
//타일 갯수
#define TILE_COUNT_X 64
#define TILE_COUNT_Y 64

//타일 이미지
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
	int left, top, right, bottom; // x, y 값(rect의 left, top)

	RECT rect;

	//int index; // 색인값. tileNum, tileKind, tilePos 에서 사용.

	//int tileNum[TILE_MAX]; // 샘플타일 인덱스(선택된 창) index를 가져와서 담음.
	TILEKIND tileKind; // 오브젝트, 타일 구분.
	POINT tilePos; // 샘플타일에서 골라진녀석(frameX, frameY)


	//int height; // 쌓일수록 커지는 높이
};
