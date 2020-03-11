#include "stdafx.h"
#include "ResourceCollection.h"


ResourceCollection::ResourceCollection()
{
}


ResourceCollection::~ResourceCollection()
{
}

HRESULT ResourceCollection::Init()
{
	// 맵툴용 이미지들
	IMAGEMANAGER->AddFrameImage("BaseMap", "images/MapTile/BaseMap.bmp",
		0, 0, 32 * 16 * 2, 32 * 17 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("MapTile1", "images/MapTile/MapTile1.bmp",
		0, 0, 32 * 16 * 2, 32 * 17 * 2, 16, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("MapTile2", "images/MapTile/MapTile2.bmp",
		0, 0, 32 * 16 * 2, 32 * 17 * 2, 16, 17, true, RGB(255, 0, 255));

	// UI 이미지
	IMAGEMANAGER->AddImage("ZurgConsole", "images/UI/ZurgConsole.bmp", WINSIZEX, WINSIZEY, true, RGB(0, 222, 0));

	// 셀렉트 원
	IMAGEMANAGER->AddImage("4X3", "images/UI/4X3.bmp", 300, 300, true, RGB(255, 0, 255));

	// 프로그래스바
	IMAGEMANAGER->AddImage("ZurgProgressBack", "images/UI/ZurgProgressBack.bmp", 107 * 2, 9 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ZurgProgressFront", "images/UI/ZurgProgressFront.bmp", 107 * 2, 9 * 2, true, RGB(255, 0, 255));

	// 해처리 이미지, 애니메이션
	IMAGEMANAGER->AddFrameImage("Hatchery", "images/Building/Hatchery.bmp", 1152 * 2, 160 * 2, 6, 1, true, RGB(0, 222, 0));
	ANIMATIONMANAGER->AddAnimation("HatcheryAnimation", "Hatchery", 0, 4, 5, true, true);

	

	
	return S_OK;
}

void ResourceCollection::Release()
{
}

void ResourceCollection::Update()
{
}

void ResourceCollection::Render()
{
}
