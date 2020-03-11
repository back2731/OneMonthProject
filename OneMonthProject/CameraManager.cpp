#include "stdafx.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
}

HRESULT CameraManager::Init()
{
	camera = IMAGEMANAGER->AddImage("Ä«¸Þ¶ó", WINSIZEX, WINSIZEY);

	cameraCenter = PointMake(WINSIZEX / 2, WINSIZEY / 2);

	cameraXY = PointMake(cameraCenter.x - WINSIZEX / 2, cameraCenter.y - WINSIZEY / 2);


	return S_OK;
}

void CameraManager::relaese()
{
}

void CameraManager::Update()
{
	cameraXY = PointMake(cameraCenter.x - WINSIZEX / 2, cameraCenter.y - WINSIZEY / 2);
	//count++;
}

void CameraManager::Render(Image* img)
{
	sprintf_s(str, "x :  %d", m_ptMouse.x);
	TextOut(img->GetMemDC(), cameraCenter.x - WINSIZEX / 2, cameraCenter.y - WINSIZEY / 2, str, strlen(str));
	GdiTransparentBlt(img->GetMemDC(), cameraCenter.x - WINSIZEX / 2, cameraCenter.y - WINSIZEY / 2, WINSIZEX, WINSIZEY, camera->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(255, 255, 255));
	TIMEMANAGER->Render(img->GetMemDC());

	IMAGEMANAGER->FindImage("ZurgConsole")->Render(img->GetMemDC(), cameraCenter.x - WINSIZEX / 2, cameraCenter.y - WINSIZEY / 2);
}

void CameraManager::SetCameraCenter(POINT point)
{
	cameraCenter.x = point.x;
	cameraCenter.y = point.y;
}

void CameraManager::MoveCamera()
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT) && cameraXY.x > 0)
	{
		cameraCenter.x -= 32;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) && cameraXY.x < 32 * 100)
	{
		cameraCenter.x += 32;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_UP) && cameraXY.y > 0)
	{
		cameraCenter.y -= 32;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN) && cameraXY.y < 32 * 100)
	{
		cameraCenter.y += 32;
	}
}
