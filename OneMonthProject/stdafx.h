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
#include "ProgressBar.h"
#include "CameraManager.h"

#include "SubWindow.h"

#include "UnitManager.h"
#include "BuildManager.h"

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
#define PROGRESSMANAGER		ProgressBar::GetSingleton()

#define BULLETMANAGER		BulletManager::GetSingleton()
#define OBJECTPOOL			ObjectPool::GetSingleton()
#define COLLISIONMANAGER	CollisionManager::GetSingleton()

#define CAMERAMANAGER		CameraManager::GetSingleton()
#define UNITMANAGER			UnitManager::GetSingleton()
#define BUILDMANAGER		BuildManager::GetSingleton()

//======================================
//##			디파인문				  ##
//======================================

#define WINNAME		(LPTSTR)(TEXT("The Binding of Isaac"))
#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1200
#define	WINSIZEY	900
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

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
