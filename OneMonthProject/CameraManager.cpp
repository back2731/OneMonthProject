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
	//sprintf_s(str, "count :  %d", count);
	//TextOut(img->GetMemDC(), cameraCenter.x - WINSIZEX / 2, cameraCenter.y - WINSIZEY / 2, str, strlen(str));
	GdiTransparentBlt(img->GetMemDC(), cameraCenter.x - WINSIZEX / 2, cameraCenter.y - WINSIZEY / 2, WINSIZEX, WINSIZEY, camera->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(255, 255, 255));
	TIMEMANAGER->Render(img->GetMemDC());
}

void CameraManager::SetCameraCenter(POINT point)
{
	cameraCenter.x = point.x;
	cameraCenter.y = point.y;
}
