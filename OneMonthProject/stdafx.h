// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#include<commdlg.h>//오빨넴용(openFileName)


//STL
#include <vector>
#include <map>
#include <string>




// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

//======================================
//##내가 만든 헤더파일은 이곳에 추가하자.##
//======================================
#include "CommonMacroFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "AnimationManager.h"
#include "EffectManager.h"
#include "RandomFunction.h"
#include "Utils.h"
#include "TxtData.h"

#include "ObjectPool.h"
#include "BulletManager.h"
#include "CollisionManager.h"
#include "CameraManager.h"

#include "SubWindow.h"

#include "UnitManager.h"
#include "BuildManager.h"
#include "CommandManager.h"
#include "PlayerManager.h"
#include "UpgradeManager.h"

using namespace UTIL;


//======================================
//##			매니저들			  ##
//======================================
#define KEYMANAGER			KeyManager::GetSingleton()
#define IMAGEMANAGER		ImageManager::GetSingleton()
#define TIMEMANAGER			TimeManager::GetSingleton()
#define SCENEMANAGER		SceneManager::GetSingleton()
#define SOUNDMANAGER		SoundManager::GetSingleton()
#define ANIMATIONMANAGER	AnimationManager::GetSingleton()
#define EFFECTMANAGER		EffectManager::GetSingleton()
#define RND					RandomFunction::GetSingleton()
#define TXTDATA				TxtData::GetSingleton()
#define SUBWIN				SubWindow::GetSingleton()

#define BULLETMANAGER		BulletManager::GetSingleton()
#define OBJECTPOOL			ObjectPool::GetSingleton()
#define COLLISIONMANAGER	CollisionManager::GetSingleton()

#define CAMERAMANAGER		CameraManager::GetSingleton()
#define UNITMANAGER			UnitManager::GetSingleton()
#define BUILDMANAGER		BuildManager::GetSingleton()
#define COMMANDMANAGER		CommandManager::GetSingleton()
#define PLAYERMANAGER		PlayerManager::GetSingleton()
#define UPGRADEMANAGER		UpgradeManager::GetSingleton()

//======================================
//##			디파인문				  ##
//======================================

#define WINNAME		(LPTSTR)(TEXT("StarCraft"))
#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1200
#define	WINSIZEY	900
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define BULLETMAX	10000
#define SUBWINSIZEX 32*16
#define SUBWINSIZEY 900

//크기
#define CELL_WIDTH	64
#define CELL_HEIGHT 64

//타일 갯수
#define TILE_COUNT_X 64
#define TILE_COUNT_Y 64

//타일 이미지
#define TILE_SIZE_X 16
#define TILE_SIZE_Y 17

#define TILE_MAX 1

#define TILEX 64
#define TILEY 64
#define TILESIZE TILEX*TILEY

#define LARVAMAX 3
#define LARVAMOVEPOWER 1

//======================================
//## 메인게임 릴리즈에서 사용하는 녀석	##
//======================================
#define SAFE_DELETE(p) {if(p) {delete(p); (p) = nullptr;}}



//================================================
//## 전역변수(인스턴스, 윈도우 핸들, 마우스 좌표)	##
//================================================

extern HINSTANCE m_hInstance;
extern HWND m_hWnd;
extern POINT m_ptMouse;
