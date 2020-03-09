#pragma once
#include"Image.h"

//백버퍼 이미지를 스태틱으로 변경

//static Image* _backBuffer = IMAGEMANAGER->AddImage("backbuffer", WINSIZEX, WINSIZEY);
class GameNode
{

private:
	static Image* _backBuffer;		//백버퍼

	//void SetBackBuffer();		//백버퍼 셋팅

	HDC _hdc;
	bool _managerInit;

public:
	GameNode();
	~GameNode();


	virtual HRESULT Init();
	virtual HRESULT Init(bool managerInit);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render();


	static Image* SetBackBuffer();

	//백버퍼 얻어오기
	Image* GetBackBuffer() { return _backBuffer; }

	//추가(메모리 DC)
	HDC GetMemDC() { return _backBuffer->GetMemDC(); }

	//추가 HDC얻기
	HDC GetHDC() { return _hdc; }


	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

