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
	IMAGEMANAGER->AddFrameImage("BaseMapCreep", "images/MapTile/BaseMapCreep.bmp",
		0, 0, 1536, 1536, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("MapTile1", "images/MapTile/MapTile1.bmp",
		0, 0, 32 * 16 * 2, 32 * 17 * 2, 16, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("MapTile2", "images/MapTile/MapTile2.bmp",
		0, 0, 32 * 16 * 2, 32 * 17 * 2, 16, 17, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddFrameImage("test1", "images/MapTile/test1.bmp",
		0, 0, 96 * 1 * 2, 96 * 1 * 2, 1, 1, true, RGB(255, 0, 255));
	
	// 미니맵
	IMAGEMANAGER->AddImage("miniMap", "images/MapTile/miniMap.bmp", 812, 900, true, RGB(255, 0, 255));

	// 타이틀 및 메뉴 UI
	IMAGEMANAGER->AddImage("title", "images/UI/menu/title.bmp", WINSIZEX, WINSIZEY, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("background", "images/UI/menu/background.bmp", WINSIZEX, WINSIZEY, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("singlePlay", "images/UI/menu/singlePlay.bmp", 11200 * IMAGESIZECONTROL, 116 * IMAGESIZECONTROL, 35, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("singlePlayOverlay", "images/UI/menu/singlePlayOverlay.bmp", 15120 * IMAGESIZECONTROL, 116 * IMAGESIZECONTROL, 60, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("mapTool", "images/UI/menu/mapTool.bmp", 13600 * IMAGESIZECONTROL, 140 * IMAGESIZECONTROL, 85, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("mapToolOverlay", "images/UI/menu/mapToolOverlay.bmp", 4080 * IMAGESIZECONTROL, 132 * IMAGESIZECONTROL, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("exit", "images/UI/menu/exit.bmp", 9200 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 50, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("exitOverlay", "images/UI/menu/exitOverlay.bmp", 6480 * IMAGESIZECONTROL, 136 * IMAGESIZECONTROL, 30, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("multiPlay", "images/UI/menu/multiPlay.bmp", 13000 * IMAGESIZECONTROL, 176 * IMAGESIZECONTROL, 50, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("multiPlayOverlay", "images/UI/menu/multiPlayOverlay.bmp", 5280 * IMAGESIZECONTROL, 148 * IMAGESIZECONTROL, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("multiPlayTail", "images/UI/menu/multiPlayTail.bmp", 90 * IMAGESIZECONTROL, 116 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("singlePlayText", "images/UI/menu/singlePlayText.bmp", 229, 53, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("exitText", "images/UI/menu/exitText.bmp", 86, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mapToolText", "images/UI/menu/mapToolText.bmp", 180, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("multiPlayText", "images/UI/menu/multiPlayText.bmp", 187, 41, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("black", "images/UI/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("defeat", "images/UI/defeat.bmp", 666, 288, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("victory", "images/UI/victory.bmp", 666, 288, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("escMenu", "images/UI/escMenu.bmp", 612, 648, true, RGB(255, 0, 255));

	// UI 이미지
	IMAGEMANAGER->AddImage("ZergConsole", "images/UI/ZergConsole.bmp", WINSIZEX, WINSIZEY, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("population", "images/UI/population.bmp", 14 * IMAGESIZECONTROL, 14 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mineral", "images/UI/mineral.bmp", 14 * IMAGESIZECONTROL, 14 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("gas", "images/UI/gas.bmp", 14 * IMAGESIZECONTROL, 14 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	
	// 마우스 커서
	IMAGEMANAGER->AddFrameImage("Cursor", "images/UI/Cursor.bmp", 100 * IMAGESIZECONTROL, 21 * IMAGESIZECONTROL, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("drag", "images/UI/drag.bmp", 18 * IMAGESIZECONTROL, 22 * IMAGESIZECONTROL, 1, 1, true, RGB(255, 0, 255));

	// 셀렉트 원
	IMAGEMANAGER->AddImage("4X3", "images/UI/4X3.bmp", 300, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("1X1", "images/UI/1X1.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("2X2", "images/UI/2X2.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("3X2", "images/UI/3X2.bmp", 230, 230, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("enemy4X3", "images/UI/enemy4X3.bmp", 300, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("enemy1X1", "images/UI/enemy1X1.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("enemy2X2", "images/UI/enemy2X2.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("enemy3X2", "images/UI/enemy3X2.bmp", 230, 230, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("2X2Building", "images/UI/3X2.bmp", 180, 180, true, RGB(255, 0, 255));

	// 프로그래스바
	IMAGEMANAGER->AddImage("ZergProgressBack", "images/UI/ZergProgressBack.bmp", 107 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ZergProgressFront", "images/UI/ZergProgressFront.bmp", 107 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("ZergUnitProgressBack", "images/UI/ZergUnitProgressBack.bmp", 29 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ZergUnitProgressFront", "images/UI/ZergUnitProgressFront.bmp", 29 * IMAGESIZECONTROL, 9 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 건물 생산 이미지
	IMAGEMANAGER->AddFrameImage("buildingBirthSmall", "images/Building/buildingBirthSmall.bmp", 2400 * IMAGESIZECONTROL, 133 * IMAGESIZECONTROL, 15, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("buildingBirthMiddle", "images/Building/buildingBirthMiddle.bmp", 3360 * IMAGESIZECONTROL, 133 * IMAGESIZECONTROL, 21, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("buildingBirthBig", "images/Building/buildingBirthBig.bmp", 2880 * IMAGESIZECONTROL, 150 * IMAGESIZECONTROL, 18, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("transToLair", "images/Building/transToLair.bmp", 3360 * IMAGESIZECONTROL, 133 * IMAGESIZECONTROL, 21, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("transToHive", "images/Building/transToHive.bmp", 2880 * IMAGESIZECONTROL, 150 * IMAGESIZECONTROL, 18, 1, true, RGB(0, 222, 0));
	
	// 해처리 이미지
	IMAGEMANAGER->AddFrameImage("Hatchery", "images/Building/Hatchery.bmp", 960 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 5, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("HatcheryWirefram", "images/Building/HatcheryWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("EnemyHatchery", "images/Building/EnemyHatchery.bmp", 768 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 6, 1, true, RGB(0, 222, 0));
	
	IMAGEMANAGER->AddFrameImage("Lair", "images/Building/Lair.bmp", 960 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 5, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("LairWirefram", "images/Building/LairWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddFrameImage("Hive", "images/Building/Hive.bmp", 960 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 5, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("HiveWirefram", "images/Building/HiveWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// 크립 콜로니 이미지
	IMAGEMANAGER->AddFrameImage("CreepColony", "images/Building/CreepColony.bmp", 512 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, 4, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("CreepColonyWirefram", "images/Building/CreepColonyWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// 익스트렉터 이미지
	IMAGEMANAGER->AddFrameImage("Extractor", "images/Building/Extractor.bmp", 512 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 4, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("ExtractorWirefram", "images/Building/ExtractorWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 스포닝풀 이미지
	IMAGEMANAGER->AddFrameImage("SpawningPool", "images/Building/SpawningPool.bmp", 384 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, 4, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("SpawningPoolWirefram", "images/Building/SpawningPoolWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// 에볼루션챔버 이미지
	IMAGEMANAGER->AddFrameImage("EvolutionChamber", "images/Building/EvolutionChamber.bmp", 360 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 3, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("EvolutionWirefram", "images/Building/EvolutionWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 히드라리스크덴 이미지
	IMAGEMANAGER->AddFrameImage("HydraliskDen", "images/Building/HydraliskDen.bmp", 288 * IMAGESIZECONTROL, 84 * IMAGESIZECONTROL, 3, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("HydraliskDenWirefram", "images/Building/HydraliskDenWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 스파이어 이미지
	IMAGEMANAGER->AddFrameImage("Spire", "images/Building/Spire.bmp", 360 * IMAGESIZECONTROL, 104 * IMAGESIZECONTROL, 3, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("SpireWirefram", "images/Building/SpireWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 퀸즈네스트 이미지
	IMAGEMANAGER->AddFrameImage("QueensNest", "images/Building/QueensNest.bmp", 360 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 3, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("QueensNestWirefram", "images/Building/QueensNestWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	 
	// 울트라리스크 캐번 이미지
	IMAGEMANAGER->AddFrameImage("UltraliskCavern", "images/Building/UltraliskCavern.bmp", 360 * IMAGESIZECONTROL, 104 * IMAGESIZECONTROL, 3, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("UltraliskCavernWirefram", "images/Building/UltraliskCavernWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 디파일러 마운드 캐번 이미지
	IMAGEMANAGER->AddFrameImage("DefilerMound", "images/Building/DefilerMound.bmp", 360 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 3, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("DefilerMoundWirefram", "images/Building/DefilerMoundWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 라바 이미지
	IMAGEMANAGER->AddFrameImage("larva", "images/Unit/larva.bmp", 180 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL * 16, 5, 16, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("enemyLarva", "images/Unit/enemyLarva.bmp", 180 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL * 16, 5, 16, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("larvaWirefram", "images/Unit/larvaWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// 드론 이미지
	IMAGEMANAGER->AddFrameImage("drone", "images/Unit/droneTest.bmp", 1280 * IMAGESIZECONTROL, 1152 * IMAGESIZECONTROL, 10, 9, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("droneBirth", "images/Unit/droneBirth.bmp", 3072 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 32, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("droneWirefram", "images/Unit/droneWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 저글링 이미지
	IMAGEMANAGER->AddFrameImage("zergling", "images/Unit/zergling.bmp", 1536 * 3 / IMAGESIZECONTROL, 1152 * 3 / IMAGESIZECONTROL, 12, 9, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("zerglingBirth", "images/Unit/zerglingBirth.bmp", 2976 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 31, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("zerglingWirefram", "images/Unit/zerglingWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("enemyZergling", "images/Unit/enemyZergling.bmp", 1536 * 3 / IMAGESIZECONTROL, 1152 * 3 / IMAGESIZECONTROL, 12, 9, true, RGB(0, 222, 0));

	// 오버로드 이미지
	IMAGEMANAGER->AddFrameImage("overlord", "images/Unit/overlord.bmp", 1008 * IMAGESIZECONTROL, 672 * IMAGESIZECONTROL, 12, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("overlordShadow", "images/Unit/overlordShadow.bmp", 1008 * IMAGESIZECONTROL, 672 * IMAGESIZECONTROL, 12, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("overlordBirth", "images/Unit/overlordBirth.bmp", 2976 * IMAGESIZECONTROL, 125 * IMAGESIZECONTROL, 31, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("overlordWirefram", "images/Unit/overlordWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// 히드라 이미지
	IMAGEMANAGER->AddFrameImage("hydra", "images/Unit/hydra.bmp", 1536 * IMAGESIZECONTROL, 1024 * IMAGESIZECONTROL, 12, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("hydraBirth", "images/Unit/hydraBirth.bmp", 2976 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, 31, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("hydraWirefram", "images/Unit/hydraWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 뮤탈리스크 이미지
	IMAGEMANAGER->AddFrameImage("mutalisk", "images/Unit/mutalisk.bmp", 640 * IMAGESIZECONTROL, 1012 * IMAGESIZECONTROL, 5, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("mutaliskShadow", "images/Unit/mutaliskShadow.bmp", 640 * IMAGESIZECONTROL, 1012 * IMAGESIZECONTROL, 5, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("mutaliskBirth", "images/Unit/mutaliskBirth.bmp", 2976 * IMAGESIZECONTROL, 125 * IMAGESIZECONTROL, 31, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutaliskWirefram", "images/Unit/mutaliskWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 스커지 이미지
	IMAGEMANAGER->AddFrameImage("scourge", "images/Unit/scourge.bmp", 240 * IMAGESIZECONTROL, 384* IMAGESIZECONTROL, 5, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("scourgeShadow", "images/Unit/scourgeShadow.bmp", 240 * IMAGESIZECONTROL, 384* IMAGESIZECONTROL, 5, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("scourgeBirth", "images/Unit/scourgeBirth.bmp", 2976 * IMAGESIZECONTROL, 125 * IMAGESIZECONTROL, 31, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("scourgeWirefram", "images/Unit/scourgeWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 퀸 이미지
	IMAGEMANAGER->AddFrameImage("queen", "images/Unit/queen.bmp", 1408 * 3 / IMAGESIZECONTROL, 1024 * 3 / IMAGESIZECONTROL, 11, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("queenShadow", "images/Unit/queenShadow.bmp", 1408 * 3 / IMAGESIZECONTROL, 1024 * 3 / IMAGESIZECONTROL, 11, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("queenBirth", "images/Unit/queenBirth.bmp", 2976 * IMAGESIZECONTROL, 125 * IMAGESIZECONTROL, 31, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("queenWirefram", "images/Unit/queenWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// 울트라리스크 이미지
	IMAGEMANAGER->AddFrameImage("Ultralisk", "images/Unit/Ultralisk.bmp", 1920 * IMAGESIZECONTROL, 1024 * IMAGESIZECONTROL, 15, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("ultraBirth", "images/Unit/ultraBirth.bmp", 2880 * IMAGESIZECONTROL, 125 * IMAGESIZECONTROL, 30, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("UltraliskWirefram", "images/Unit/UltraliskWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	// 디파일러 이미지
	IMAGEMANAGER->AddFrameImage("defiler", "images/Unit/defiler.bmp", 640 * IMAGESIZECONTROL, 640* IMAGESIZECONTROL, 8, 8, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("defilerBirth", "images/Unit/defilerBirth.bmp", 2880 * IMAGESIZECONTROL, 125 * IMAGESIZECONTROL, 30, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("defilerWirefram", "images/Unit/defilerWirefram.bmp", 64 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 아이콘
	IMAGEMANAGER->AddImage("SelectLarva", "images/UI/Icon/Hatchery/SelectLarva.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("SetRallyPoint", "images/UI/Icon/Hatchery/SetRallyPoint.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("EvolveBurrow", "images/UI/Icon/Hatchery/EvolveBurrow.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("LairRequires", "images/UI/Icon/Hatchery/LairRequires.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledLairRequires", "images/UI/Icon/Hatchery/DisabledLairRequires.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickLairRequires", "images/UI/Icon/Hatchery/ClickLairRequires.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("HiveRequires", "images/UI/Icon/Hatchery/HiveRequires.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledHiveRequires", "images/UI/Icon/Hatchery/DisabledHiveRequires.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickHiveRequires", "images/UI/Icon/Hatchery/ClickHiveRequires.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("TransformDrone", "images/UI/Icon/Larva/TransformDrone.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickDrone", "images/UI/Icon/Larva/ClickDrone.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("DisabledZergling", "images/UI/Icon/Larva/DisabledZergling.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("TransformZergling", "images/UI/Icon/Larva/TransformZergling.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickZergling", "images/UI/Icon/Larva/ClickZergling.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("TransformOverlord", "images/UI/Icon/Larva/TransformOverlord.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickOverlord", "images/UI/Icon/Larva/ClickOverlord.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("TransformHydralisk", "images/UI/Icon/Larva/TransformHydralisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledHydralisk", "images/UI/Icon/Larva/DisabledHydralisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickHydralisk", "images/UI/Icon/Larva/ClickHydralisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("TransformMutalisk", "images/UI/Icon/Larva/TransformMutalisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledMutalisk", "images/UI/Icon/Larva/DisabledMutalisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickMutalisk", "images/UI/Icon/Larva/ClickMutalisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("TransformScourge", "images/UI/Icon/Larva/TransformScourge.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledScourge", "images/UI/Icon/Larva/DisabledScourge.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickScourge", "images/UI/Icon/Larva/ClickScourge.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("TransformQueen", "images/UI/Icon/Larva/TransformQueen.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledQueen", "images/UI/Icon/Larva/DisabledQueen.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickQueen", "images/UI/Icon/Larva/ClickQueen.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("TransformUltralisk", "images/UI/Icon/Larva/TransformUltralisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledUltralisk", "images/UI/Icon/Larva/DisabledUltralisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickUltralisk", "images/UI/Icon/Larva/ClickUltralisk.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("TransformDefiler", "images/UI/Icon/Larva/TransformDefiler.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledDefiler", "images/UI/Icon/Larva/DisabledDefiler.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickDefiler", "images/UI/Icon/Larva/ClickDefiler.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("evolveVentralSacs", "images/UI/Icon/Hatchery/evolveVentralSacs.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("evolveAntennae", "images/UI/Icon/Hatchery/evolveAntennae.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("evolvePneumatizedCarapace", "images/UI/Icon/Hatchery/evolvePneumatizedCarapace.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("ClickEvolveVentralSacs", "images/UI/Icon/Hatchery/ClickEvolveVentralSacs.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickEvolveAntennae", "images/UI/Icon/Hatchery/ClickEvolveAntennae.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickEvolvePneumatizedCarapace", "images/UI/Icon/Hatchery/ClickEvolvePneumatizedCarapace.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 에볼루션 챔버 아이콘
	IMAGEMANAGER->AddImage("evolveCarapaceIcon", "images/UI/Icon/ability/evolveCarapaceIcon.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("upgradeMeleeAttackIcon", "images/UI/Icon/ability/upgradeMeleeAttackIcon.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("upgradeMissileAttackIcon", "images/UI/Icon/ability/upgradeMissileAttackIcon.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledEvolveCarapaceIcon", "images/UI/Icon/ability/DisabledEvolveCarapaceIcon.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledUpgradeMeleeAttackIcon", "images/UI/Icon/ability/DisabledUpgradeMeleeAttackIcon.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledUpgradeMissileAttackIcon", "images/UI/Icon/ability/DisabledUpgradeMissileAttackIcon.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickEvolveCarapaceIcon", "images/UI/Icon/ability/ClickEvolveCarapaceIcon.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickUpgradeMeleeAttackIcon", "images/UI/Icon/ability/ClickUpgradeMeleeAttackIcon.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickUpgradeMissileAttackIcon", "images/UI/Icon/ability/ClickUpgradeMissileAttackIcon.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("upgradeMeleeAttacks", "images/UI/description/upgradeMeleeAttacks.bmp", 261, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("upgradeMeleeAttacks2", "images/UI/description/upgradeMeleeAttacks2.bmp", 261, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("upgradeMeleeAttacks3", "images/UI/description/upgradeMeleeAttacks3.bmp", 260, 107, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("meleeAttacksL2Require", "images/UI/description/meleeAttacksL2Require.bmp", 247, 73, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("meleeAttacksL3Require", "images/UI/description/meleeAttacksL3Require.bmp", 247, 73, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("upgradeMissileAttacks", "images/UI/description/upgradeMissileAttacks.bmp", 266, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("upgradeMissileAttacks2", "images/UI/description/upgradeMissileAttacks2.bmp", 264, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("upgradeMissileAttacks3", "images/UI/description/upgradeMissileAttacks3.bmp", 266, 107, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("missileAttacksL2Require", "images/UI/description/missileAttacksL2Require.bmp", 247, 73, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("missileAttacksL3Require", "images/UI/description/missileAttacksL3Require.bmp", 247, 73, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("evolveCarapace", "images/UI/description/evolveCarapace.bmp", 196, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("evolveCarapace2", "images/UI/description/evolveCarapace2.bmp", 196, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("evolveCarapace3", "images/UI/description/evolveCarapace3.bmp", 196, 107, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("carapaceL2Requires", "images/UI/description/carapaceL2Requires.bmp", 213, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("carapaceL3Requires", "images/UI/description/carapaceL3Requires.bmp", 213, 74, true, RGB(255, 0, 255));

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
	IMAGEMANAGER->AddImage("DisabledEvolutionChamber", "images/UI/Icon/Drone/BaseBuilding/DisabledEvolutionChamber.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickEvolutionChamber", "images/UI/Icon/Drone/BaseBuilding/ClickEvolutionChamber.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("HydraliskDenUI", "images/UI/Icon/Drone/BaseBuilding/HydraliskDen.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledHydraliskDen", "images/UI/Icon/Drone/BaseBuilding/DisabledHydraliskDen.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickHydraliskDen", "images/UI/Icon/Drone/BaseBuilding/ClickHydraliskDen.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("SpawningPoolUI", "images/UI/Icon/Drone/BaseBuilding/SpawningPool.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledSpawningPool", "images/UI/Icon/Drone/BaseBuilding/DisabledSpawningPool.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickSpawningPool", "images/UI/Icon/Drone/BaseBuilding/ClickSpawningPool.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("SunkenColonyUI", "images/UI/Icon/Drone/BaseBuilding/SunkenColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledSunkenColony", "images/UI/Icon/Drone/BaseBuilding/DisabledSunkenColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickSunkenColony", "images/UI/Icon/Drone/BaseBuilding/ClickSunkenColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("SporeColonyUI", "images/UI/Icon/Drone/BaseBuilding/SporeColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledSporeColony", "images/UI/Icon/Drone/BaseBuilding/DisabledSporeColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickDisabledSporeColony", "images/UI/Icon/Drone/BaseBuilding/ClickDisabledSporeColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("CreepColonyUI", "images/UI/Icon/Drone/BaseBuilding/CreepColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickCreepColony", "images/UI/Icon/Drone/BaseBuilding/ClickCreepColony.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("ExtractorUI", "images/UI/Icon/Drone/BaseBuilding/Extractor.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickExtractor", "images/UI/Icon/Drone/BaseBuilding/ClickExtractor.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("HatcheryUI", "images/UI/Icon/Drone/BaseBuilding/Hatchery.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickHatchery", "images/UI/Icon/Drone/BaseBuilding/ClickHatchery.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// High 건물
	IMAGEMANAGER->AddImage("UltraliskCavernUI", "images/UI/Icon/Drone/HighBuilding/UltraliskCavern.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledUltraliskCavern", "images/UI/Icon/Drone/HighBuilding/DisabledUltraliskCavern.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickUltraliskCavern", "images/UI/Icon/Drone/HighBuilding/ClickUltraliskCavern.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("DefilerMoundUI", "images/UI/Icon/Drone/HighBuilding/DefilerMound.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledDefilerMound", "images/UI/Icon/Drone/HighBuilding/DisabledDefilerMound.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickDefilerMound", "images/UI/Icon/Drone/HighBuilding/ClickDefilerMound.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("GreaterSpireUI", "images/UI/Icon/Drone/HighBuilding/GreaterSpire.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledGreaterSpire", "images/UI/Icon/Drone/HighBuilding/DisabledGreaterSpire.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickGreaterSpire", "images/UI/Icon/Drone/HighBuilding/ClickGreaterSpire.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("NydusCanalUI", "images/UI/Icon/Drone/HighBuilding/NydusCanal.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledNydusCanal", "images/UI/Icon/Drone/HighBuilding/DisabledNydusCanal.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickNydusCanal", "images/UI/Icon/Drone/HighBuilding/ClickNydusCanal.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("QueensNestUI", "images/UI/Icon/Drone/HighBuilding/QueensNest.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledQueensNest", "images/UI/Icon/Drone/HighBuilding/DisabledQueensNest.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickQueensNest", "images/UI/Icon/Drone/HighBuilding/ClickQueensNest.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("SpireUI", "images/UI/Icon/Drone/HighBuilding/Spire.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DisabledSpire", "images/UI/Icon/Drone/HighBuilding/DisabledSpire.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ClickSpire", "images/UI/Icon/Drone/HighBuilding/ClickSpire.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 마우스를 갖다 댔을때 나오는 UI
	IMAGEMANAGER->AddImage("morphToDrone", "images/UI/description/morphToDrone.bmp", 194, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("morphToZerglings", "images/UI/description/morphToZerglings.bmp", 221, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("morphToOverlord", "images/UI/description/morphToOverlord.bmp", 218, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("morphToHydralisk", "images/UI/description/morphToHydralisk.bmp", 223, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("morphToMutalisk", "images/UI/description/morphToMutalisk.bmp", 218, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("morphToScourge", "images/UI/description/morphToScourge.bmp", 210, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("morphToQueen", "images/UI/description/morphToQueen.bmp", 210, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("morphToUltralisk", "images/UI/description/morphToUltralisk.bmp", 214, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("morphTodefiler", "images/UI/description/morphTodefiler.bmp", 198, 84, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("zerglingsRequires", "images/UI/description/zerglingsRequires.bmp", 178, 78, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("hydraliskRequires", "images/UI/description/hydraliskRequires.bmp", 190, 78, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutaliskRequires", "images/UI/description/mutaliskRequires.bmp", 180, 78, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("scourgeRequires", "images/UI/description/scourgeRequires.bmp", 169, 78, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("queenRequires", "images/UI/description/queenRequires.bmp", 162, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ultraliskRequires", "images/UI/description/ultraliskRequires.bmp", 180, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("defilerRequires", "images/UI/description/defilerRequires.bmp", 164, 75, true, RGB(255, 0, 255));
	
	// 기본 베이스 마우스 UI
	IMAGEMANAGER->AddImage("MoveUI", "images/UI/description/MoveUI.bmp", 101, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("StopUI", "images/UI/description/StopUI.bmp", 88, 49, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("AttackUI", "images/UI/description/AttackUI.bmp", 107, 49, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("PatrolUI", "images/UI/description/PatrolUI.bmp", 103, 49, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("holdPositionUI", "images/UI/description/holdPositionUI.bmp", 171, 49, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GatherUI", "images/UI/description/GatherUI.bmp", 110, 49, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("BasicMutationUI", "images/UI/description/BasicMutationUI.bmp", 185, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("advancedMutationUI", "images/UI/description/advancedMutationUI.bmp", 223, 49, true, RGB(255, 0, 255));
	



	// 베이스 건물 마우스 UI
	IMAGEMANAGER->AddImage("mutateIntoHatchery", "images/UI/description/mutateIntoHatchery.bmp", 244, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutateIntoCreepColony", "images/UI/description/mutateIntoCreepColony.bmp", 277, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutateIntoExtractor", "images/UI/description/mutateIntoExtractor.bmp", 243, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutateIntoSpawningPool", "images/UI/description/mutateIntoSpawningPool.bmp", 293, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutateIntoEvolutionChamber", "images/UI/description/mutateIntoEvolutionChamber.bmp", 331, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutateIntoHydraliskDen", "images/UI/description/mutateIntoHydraliskDen.bmp", 287, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("hydraliskDenRequires", "images/UI/description/hydraliskDenRequires.bmp", 230, 79, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("ESCcancelUI", "images/UI/description/ESCcancelUI.bmp", 126, 48, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("mutateIntoSpire", "images/UI/description/mutateIntoSpire.bmp", 205, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutateIntoQueensNest", "images/UI/description/mutateIntoQueensNest.bmp", 279, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutateIntoNydusCanal", "images/UI/description/mutateIntoNydusCanal.bmp", 272, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutateIntoUltraliskCavern", "images/UI/description/mutateIntoUltraliskCavern.bmp", 304, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("mutateIntoDefilerMound", "images/UI/description/mutateIntoDefilerMound.bmp", 290, 83, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("spireRequires", "images/UI/description/spireRequires.bmp", 151, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("queensNestRequires", "images/UI/description/queensNestRequires.bmp", 221, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("nydusCanalRequires", "images/UI/description/nydusCanalRequires.bmp", 216, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ultraliskCavernRequires", "images/UI/description/ultraliskCavernRequires.bmp", 248, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("defilerMoundRequires", "images/UI/description/defilerMoundRequires.bmp", 232, 75, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("mutateIntoLair", "images/UI/description/mutateIntoLair.bmp", 192, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("lairRequires", "images/UI/description/lairRequires.bmp", 167, 79, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("mutateIntoHive", "images/UI/description/mutateIntoHive.bmp", 202, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("hiveRequires", "images/UI/description/hiveRequires.bmp", 149, 75, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->AddImage("selectLarva", "images/UI/description/selectLarva.bmp", 157, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("setRallyPoint", "images/UI/description/setRallyPoint.bmp", 180, 49, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("evolveBurrow", "images/UI/description/evolveBurrow.bmp", 234, 112, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("burrowUI", "images/UI/description/burrowUI.bmp", 117, 49, true, RGB(255, 0, 255));

	// 오버로드 업그레이드 마우스 이미지
	IMAGEMANAGER->AddImage("descriptionEvolveVentralSacs", "images/UI/description/descriptionEvolveVentralSacs.bmp", 295, 113, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("descriptionEvolveAntennae", "images/UI/description/descriptionEvolveAntennae.bmp", 333, 112, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("descriptionEvolvePneumatizedCarapace", "images/UI/description/descriptionEvolvePneumatizedCarapace.bmp", 306, 112, true, RGB(255, 0, 255));

	// 건물 빌드 시 뜨는 이미지들
	IMAGEMANAGER->AddImage("Green", "images/UI/Icon/Drone/BaseBuilding/Green.bmp", 32 * IMAGESIZECONTROL, 32 * IMAGESIZECONTROL, true, RGB(0, 0, 0));
	IMAGEMANAGER->AddImage("Red", "images/UI/Icon/Drone/BaseBuilding/Red.bmp", 32 * IMAGESIZECONTROL, 32 * IMAGESIZECONTROL, true, RGB(0, 0, 0));
	
	IMAGEMANAGER->AddImage("mutateHatchery", "images/UI/Icon/Drone/BaseBuilding/mutateHatchery.bmp", 128 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutateSpawningPool", "images/UI/Icon/Drone/BaseBuilding/mutateSpawningPool.bmp", 96 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutateHydraliskDen", "images/UI/Icon/Drone/BaseBuilding/mutateHydraliskDen.bmp", 96 * IMAGESIZECONTROL, 84 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutateEvolutionChamber", "images/UI/Icon/Drone/BaseBuilding/mutateEvolutionChamber.bmp", 120 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutateCreepColony", "images/UI/Icon/Drone/BaseBuilding/mutateCreepColony.bmp", 77 * IMAGESIZECONTROL, 64 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutateExtractor", "images/UI/Icon/Drone/BaseBuilding/mutateExtractor.bmp", 128 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	
	IMAGEMANAGER->AddImage("mutateSpire", "images/UI/Icon/Drone/HighBuilding/mutateSpire.bmp", 120 * IMAGESIZECONTROL, 104 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutateQueensNest", "images/UI/Icon/Drone/HighBuilding/mutateQueensNest.bmp", 120 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutateUltraliskCavern", "images/UI/Icon/Drone/HighBuilding/mutateUltraliskCavern.bmp", 120 * IMAGESIZECONTROL, 104 * IMAGESIZECONTROL, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddImage("mutateDefilerMound", "images/UI/Icon/Drone/HighBuilding/mutateDefilerMound.bmp", 120 * IMAGESIZECONTROL, 96 * IMAGESIZECONTROL, true, RGB(0, 222, 0));

	// 유닛 어빌리티 이미지
	IMAGEMANAGER->AddImage("carapace", "images/UI/Icon/ability/carapace.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("claws", "images/UI/Icon/ability/claws.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("flyerCarapace", "images/UI/Icon/ability/flyerCarapace.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("glaveWurm", "images/UI/Icon/ability/glaveWurm.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("kaiserBlades", "images/UI/Icon/ability/kaiserBlades.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("needleSpines", "images/UI/Icon/ability/needleSpines.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("spines", "images/UI/Icon/ability/spines.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("suiside", "images/UI/Icon/ability/suiside.bmp", 36 * IMAGESIZECONTROL, 36 * IMAGESIZECONTROL, true, RGB(255, 0, 255));

	// 어빌리티 설명 이미지
	IMAGEMANAGER->AddImage("zergCarapaceUI", "images/UI/description/zergCarapaceUI.bmp", 152, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("clawsUI", "images/UI/description/clawsUI.bmp", 152, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("zergFlyerCarapaceUI", "images/UI/description/zergFlyerCarapaceUI.bmp", 196, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("glaveWurmUI", "images/UI/description/glaveWurmUI.bmp", 152, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("kaiserBladesUI", "images/UI/description/kaiserBladesUI.bmp", 152, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("needleSpinesUI", "images/UI/description/needleSpinesUI.bmp", 152, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("spinesUI", "images/UI/description/spinesUI.bmp", 152, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("suicideUI", "images/UI/description/suicideUI.bmp", 152, 74, true, RGB(255, 0, 255));

	// 이펙트 모음
	EFFECTMANAGER->AddEffect("buildingWreck", "images/Building/buildingWreck.bmp", 512 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 1, 0.01f, 10);
	EFFECTMANAGER->AddEffect("blood", "images/Building/blood.bmp", 2400 * IMAGESIZECONTROL, 200 * IMAGESIZECONTROL, 200 * IMAGESIZECONTROL, 200 * IMAGESIZECONTROL, 5, 0.1f, 10);
	EFFECTMANAGER->AddEffect("zerglingBlood", "images/Unit/zerglingBlood.bmp", 640 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 128 * IMAGESIZECONTROL, 1, 0.02f, 50);

	// 초상화
	IMAGEMANAGER->AddImage("zconover", "images/UI/portraits/zconover.bmp", 60 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("portraitsLarva", "images/UI/portraits/portraitsLarva.bmp", 1200 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 20, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsDrone", "images/UI/portraits/portraitsDrone.bmp", 4500 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 75, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsZergling", "images/UI/portraits/portraitsZergling.bmp", 4500 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 75, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsOverlord", "images/UI/portraits/portraitsOverlord.bmp", 4500 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 75, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsHydralisk", "images/UI/portraits/portraitsHydralisk.bmp", 4500 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 75, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsMutalisk", "images/UI/portraits/portraitsMutalisk.bmp", 4500 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 75, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsScourge", "images/UI/portraits/portraitsScourge.bmp", 4200 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 70, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsQueen", "images/UI/portraits/portraitsQueen.bmp", 3300 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 55, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsUltralisk", "images/UI/portraits/portraitsUltralisk.bmp", 3600 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 60, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsDefiler", "images/UI/portraits/portraitsDefiler.bmp", 3600 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 60, 1, true, RGB(0, 222, 0));
	IMAGEMANAGER->AddFrameImage("portraitsOverMind", "images/UI/portraits/portraitsOverMind.bmp", 4500 * IMAGESIZECONTROL, 56 * IMAGESIZECONTROL, 75, 1, true, RGB(0, 222, 0));

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
