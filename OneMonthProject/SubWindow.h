#pragma once
#include "SingletonBase.h"

#define SUBWINSIZEX 480
#define SUBWINSIZEY 900

enum CTRL
{
	CTRL_NUM1,
	CTRL_NUM2,
	CTRL_NUM3,

	CTRL_DRAW,
	CTRL_ERASER,
	CTRL_Init,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_MAIN,
	CTRL_END
};

class MapToolScene;
class SubWindow : public SingletonBase<SubWindow>
{
private:

	HWND hWnd;
	static POINT ptMouse;

	Image* m_backBuffer;
	GameNode* currentScene;

	HWND _btnDraw;
	HWND _btnEraser;
	HWND _btnInit;

	HWND _btnSave;
	HWND _btnLoad;

	HWND  _btnN1;
	HWND  _btnN2;
	HWND  _btnN3;

	HWND  _btnMain;

	static CTRL _currentCTRL;
	POINT clickFrame;
	int clickIndex;

	bool isActive;
	int saveCount = 0;

	MapToolScene * map;

public:
	SubWindow();
	~SubWindow();

	void Init();
	void Release();
	void Update();
	void Render();

	void SetScene(GameNode* scene);

	static LRESULT CALLBACK WndLogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetHwnd() { return hWnd; }

	static POINT GetMousePos() { return ptMouse; }

	static CTRL GetCTRL() { return _currentCTRL; }
	void SetCTRL(CTRL ctrl) { _currentCTRL = ctrl; }

	void SetIsActive(bool isActive) { this->isActive = isActive; }
	bool GetIsActive() { return isActive; }

	void SetFramePoint(POINT frame) { clickFrame = frame; }
	POINT GetFramePoint() { return clickFrame; }

	void SetFrameIndex(int index) { clickIndex = index; }
	int GetFrameIndex() { return clickIndex; }

	void SetIsoMap(MapToolScene* map) { this->map = map; }
	MapToolScene* GetMap() { return map; }

	void CreateSubWindow();
};