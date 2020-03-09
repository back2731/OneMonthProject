#pragma once
#include"Image.h"

//����� �̹����� ����ƽ���� ����

//static Image* _backBuffer = IMAGEMANAGER->AddImage("backbuffer", WINSIZEX, WINSIZEY);
class GameNode
{

private:
	static Image* _backBuffer;		//�����

	//void SetBackBuffer();		//����� ����

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

	//����� ������
	Image* GetBackBuffer() { return _backBuffer; }

	//�߰�(�޸� DC)
	HDC GetMemDC() { return _backBuffer->GetMemDC(); }

	//�߰� HDC���
	HDC GetHDC() { return _hdc; }


	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

