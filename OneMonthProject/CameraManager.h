#pragma once
#include"SingletonBase.h"
class CameraManager : public SingletonBase<CameraManager>
{
private:
	Image* camera;
	Image* mouseCursor;

	POINT cameraCenter;
	POINT cameraXY;

	int frameX;
	int frameY;
	int frameCount;
	int frameIndex;

	char str[128];
	int count;

public:
	CameraManager();
	~CameraManager();

	HRESULT Init();
	void relaese();
	void Update();
	void Render(Image* img);

	void SetCameraCenter(POINT point);

	void MoveCamera();

	POINT GetCameraCenter() { return cameraCenter; }
	POINT GetCameraXY() { return cameraXY; }

	int GetCameraCenterX() { return cameraXY.x; }
	int GetCameraCenterY() { return cameraXY.y; }
	HDC GetCameraDC() { return camera->GetMemDC(); }
};

