#include "stdafx.h"
#include "GameNode.h"
GameNode::GameNode()
{
}
GameNode::~GameNode()
{
}
Image* GameNode::_backBuffer = NULL;
Image* GameNode::SetBackBuffer()
{

	_backBuffer = new Image;
	_backBuffer->Init(10000, 10000);

	return _backBuffer;
}
HRESULT GameNode::Init()
{


	_hdc = GetDC(m_hWnd);
	_managerInit = false;
	return S_OK;
}

HRESULT GameNode::Init(bool managerInit)
{
	_hdc = GetDC(m_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{

		SetBackBuffer();
		//SetTimer(m_hWnd, 1, 10, NULL);
		KEYMANAGER->Init();
		IMAGEMANAGER->Init();
		TIMEMANAGER->Init();
		SCENEMANAGER->Init();
		SOUNDMANAGER->Init();
		ANIMATIONMANAGER->Init();
		EFFECTMANAGER->Init();
		TXTDATA->Init();
		CAMERAMANAGER->Init();
	}

	return S_OK;
}

void GameNode::Release()

{
	if (_managerInit)
	{
		//타이머 해제
		//KillTimer(m_hWnd, 1);
		KEYMANAGER->ReleaseSingleton();
		IMAGEMANAGER->ReleaseSingleton();
		TIMEMANAGER->ReleaseSingleton();
		SCENEMANAGER->ReleaseSingleton();
		SOUNDMANAGER->ReleaseSingleton();
		ANIMATIONMANAGER->ReleaseSingleton();
		EFFECTMANAGER->ReleaseSingleton();
		RND->ReleaseSingleton();
		TXTDATA->ReleaseSingleton();
		CAMERAMANAGER->ReleaseSingleton();

		KEYMANAGER->Release();
		IMAGEMANAGER->Release();
		TIMEMANAGER->Release();
		SCENEMANAGER->Release();
		ANIMATIONMANAGER->Release();
		EFFECTMANAGER->Release();
	}

	ReleaseDC(m_hWnd, _hdc);
}

void GameNode::Update()
{
	//더블버퍼 이후 사용 하지 않는다.(true->false)
	//InvalidateRect(m_hWnd, NULL, false);
	CAMERAMANAGER->Update();
}

void GameNode::Render(HDC hdc)
{
}

void GameNode::Render()
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//PAINTSTRUCT ps;
	//HDC hdc;

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		SUBWIN->SetIsActive(false);

		m_ptMouse.x = LOWORD(lParam) + CAMERAMANAGER->GetCameraCenter().x - WINSIZEX / 2;
		m_ptMouse.y = HIWORD(lParam) + CAMERAMANAGER->GetCameraCenter().y - WINSIZEY / 2;
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			//PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		//PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
