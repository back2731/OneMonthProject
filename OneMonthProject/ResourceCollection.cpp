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
	IMAGEMANAGER->AddImage("1X1", "images/UI/1X1.bmp", 40, 40, true, RGB(255, 0, 255));

	// 프로그래스바
	IMAGEMANAGER->AddImage("ZurgProgressBack", "images/UI/ZurgProgressBack.bmp", 107 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ZurgProgressFront", "images/UI/ZurgProgressFront.bmp", 107 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("ZurgUnitProgressBack", "images/UI/ZurgUnitProgressBack.bmp", 29 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ZurgUnitProgressFront", "images/UI/ZurgUnitProgressFront.bmp", 29 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 해처리 이미지
	IMAGEMANAGER->AddFrameImage("Hatchery", "images/Building/Hatchery.bmp", 1152 * IMAGESIZECONTROL, 160 * IMAGESIZECONTROL, 6, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("HatcheryWirefram", "images/Building/HatcheryWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 라바 이미지, 애니메이션
	IMAGEMANAGER->AddFrameImage("larva", "images/Unit/larvaTest.bmp", 180 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL * 16, 5, 16, true, RGB(0, 222, 0));

	// 아이콘

	IMAGEMANAGER->AddImage("SelectLarva", "images/UI/SelectLarva.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("SetRallyPoint", "images/UI/SetRallyPoint.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("EvolveBurrow", "images/UI/EvolveBurrow.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("LairRequires", "images/UI/LairRequires.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
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
