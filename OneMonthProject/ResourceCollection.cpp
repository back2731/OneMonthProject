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

	IMAGEMANAGER->AddFrameImage("test1", "images/MapTile/test1.bmp",
		0, 0, 96 * 1 * 2, 96 * 1 * 2, 1, 1, true, RGB(255, 0, 255));

	// UI 이미지
	IMAGEMANAGER->AddImage("ZergConsole", "images/UI/ZergConsole.bmp", WINSIZEX, WINSIZEY, true, RGB(0, 222, 0));

	// 마우스 커서
	IMAGEMANAGER->AddFrameImage("Cursor", "images/UI/Cursor.bmp", 100 * IMAGESIZECONTROL, 21 * IMAGESIZECONTROL, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("drag", "images/UI/drag.bmp", 18 * IMAGESIZECONTROL, 22 * IMAGESIZECONTROL, 1, 1, true, RGB(255, 0, 255));

	// 셀렉트 원
	IMAGEMANAGER->AddImage("4X3", "images/UI/4X3.bmp", 300, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("1X1", "images/UI/1X1.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("2X2", "images/UI/2X2.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("3X2", "images/UI/3X2.bmp", 230, 230, true, RGB(255, 0, 255));

	// 프로그래스바
	IMAGEMANAGER->AddImage("ZergProgressBack", "images/UI/ZergProgressBack.bmp", 107 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ZergProgressFront", "images/UI/ZergProgressFront.bmp", 107 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("ZergUnitProgressBack", "images/UI/ZergUnitProgressBack.bmp", 29 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ZergUnitProgressFront", "images/UI/ZergUnitProgressFront.bmp", 29 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 건물 생산 이미지
	IMAGEMANAGER->AddFrameImage("buildingBirthSamll", "images/Building/buildingBirthSamll.bmp", 2400 * IMAGESIZECONTROL, 133 * IMAGESIZECONTROL, 15, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("buildingBirthMiddle", "images/Building/buildingBirthMiddle.bmp", 3360 * IMAGESIZECONTROL, 133 * IMAGESIZECONTROL, 21, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("buildingBirthBig", "images/Building/buildingBirthBig.bmp", 2880 * IMAGESIZECONTROL, 150 * IMAGESIZECONTROL, 18, 1, true, RGB(0, 222, 0));
	
	// 해처리 이미지
	IMAGEMANAGER->AddFrameImage("Hatchery", "images/Building/Hatchery.bmp", 768 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 6, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("HatcheryWirefram", "images/Building/HatcheryWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("EnemyHatchery", "images/Building/EnemyHatchery.bmp", 768 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 6, 1, true, RGB(0, 222, 0));

	// 스포닝풀 이미지
	IMAGEMANAGER->AddFrameImage("SpawningPool", "images/Building/SpawningPool.bmp", 384 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, 4, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("SpawningPoolWirefram", "images/Building/SpawningPoolWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 라바 이미지
	IMAGEMANAGER->AddFrameImage("larva", "images/Unit/larva.bmp", 180 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL * 16, 5, 16, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("enemyLarva", "images/Unit/enemyLarva.bmp", 180 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL * 16, 5, 16, true, RGB(0, 222, 0));
	
	// 드론 이미지
	IMAGEMANAGER->AddFrameImage("drone", "images/Unit/droneTest.bmp", 1280 * IMAGESIZECONTROL, 1152 * IMAGESIZECONTROL, 10, 9, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("droneBirth", "images/Unit/droneBirth.bmp", 3072 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 32, 1, true, RGB(0, 222, 0));

	// 저글링 이미지
	IMAGEMANAGER->AddFrameImage("zergling", "images/Unit/zerglingTest.bmp", 1536 * 3 / IMAGESIZECONTROL, 1152 * 3 / IMAGESIZECONTROL, 12, 9, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("zerglingBirth", "images/Unit/zerglingBirth.bmp", 2976 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 31, 1, true, RGB(0, 222, 0));

	// 아이콘
	IMAGEMANAGER->AddImage("SelectLarva", "images/UI/Icon/Hatchery/SelectLarva.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("SetRallyPoint", "images/UI/Icon/Hatchery/SetRallyPoint.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("EvolveBurrow", "images/UI/Icon/Hatchery/EvolveBurrow.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("LairRequires", "images/UI/Icon/Hatchery/LairRequires.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("TransformDrone", "images/UI/Icon/Larva/TransformDrone.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("TransformZergling", "images/UI/Icon/Larva/TransformZergling.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("TransformOverlord", "images/UI/Icon/Larva/TransformOverlord.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("TransformHydralisk", "images/UI/Icon/Larva/TransformHydralisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("TransformMutalisk", "images/UI/Icon/Larva/TransformMutalisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("TransformScourge", "images/UI/Icon/Larva/TransformScourge.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("TransformQueen", "images/UI/Icon/Larva/TransformQueen.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("TransformUltralisk", "images/UI/Icon/Larva/TransformUltralisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("TransformDefiler", "images/UI/Icon/Larva/TransformDefiler.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// Base (대부분 들어가는 것들)
	IMAGEMANAGER->AddImage("Attack", "images/UI/Icon/Base/Attack.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("Patrol", "images/UI/Icon/Base/Patrol.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("Cancel", "images/UI/Icon/Base/Cancel.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("Hold", "images/UI/Icon/Base/Hold.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("Move", "images/UI/Icon/Base/Move.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("Stop", "images/UI/Icon/Base/Stop.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// 드론에서 보여지는 건물 슬롯 이미지
	IMAGEMANAGER->AddImage("BaseBuilding", "images/UI/Icon/Drone/BaseBuilding.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("HighBuilding", "images/UI/Icon/Drone/HighBuilding.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("Gathering", "images/UI/Icon/Drone/Gathering.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// Base 건물
	IMAGEMANAGER->AddImage("EvolutionChamberUI", "images/UI/Icon/Drone/BaseBuilding/EvolutionChamber.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("HydraliskDenUI", "images/UI/Icon/Drone/BaseBuilding/HydraliskDen.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("SpawningPoolUI", "images/UI/Icon/Drone/BaseBuilding/SpawningPool.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("SunkenColonyUI", "images/UI/Icon/Drone/BaseBuilding/SunkenColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("SporeColonyUI", "images/UI/Icon/Drone/BaseBuilding/SporeColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("CreepColonyUI", "images/UI/Icon/Drone/BaseBuilding/CreepColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ExtractorUI", "images/UI/Icon/Drone/BaseBuilding/Extractor.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("HatcheryUI", "images/UI/Icon/Drone/BaseBuilding/Hatchery.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// High 건물
	IMAGEMANAGER->AddImage("UltraliskCavernUI", "images/UI/Icon/Drone/HighBuilding/UltraliskCavern.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DefilerMoundUI", "images/UI/Icon/Drone/HighBuilding/DefilerMound.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GreaterSpireUI", "images/UI/Icon/Drone/HighBuilding/GreaterSpire.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("NydusCanalUI", "images/UI/Icon/Drone/HighBuilding/NydusCanal.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("QueensNestUI", "images/UI/Icon/Drone/HighBuilding/QueensNest.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("SpireUI", "images/UI/Icon/Drone/HighBuilding/Spire.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));


	// 건물 빌드 시 뜨는 이미지들
	IMAGEMANAGER->AddImage("Green", "images/UI/Icon/Drone/BaseBuilding/Green.bmp", 32 * IMAGESIZECONTROL, 32 * IMAGESIZECONTROL, true, RGB(0, 0, 0));
	IMAGEMANAGER->AddImage("Red", "images/UI/Icon/Drone/BaseBuilding/Red.bmp", 32 * IMAGESIZECONTROL, 32 * IMAGESIZECONTROL, true, RGB(0, 0, 0));
	IMAGEMANAGER->AddImage("mutateHatchery", "images/UI/Icon/Drone/BaseBuilding/mutateHatchery.bmp", 128 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutateSpawningPool", "images/UI/Icon/Drone/BaseBuilding/mutateSpawningPool.bmp", 96 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(0, 222, 0));

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
