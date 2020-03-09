#include "stdafx.h"
#include "KeyManager.h"


KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}

HRESULT KeyManager::Init()
{
	//Ű�� ���� �������� ���� ���·� �ʱ�ȭ����
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp.set(i, false);
		_keyDown.set(i, false);
	}

	return S_OK;
}

void KeyManager::Release()
{
}

bool KeyManager::IsOnceKeyDown(int key)
{
	//GetAsyncKeyState���� Ű�� ���¸� �˾ƿ��� �༮
	//Ű�� ������������ ���������� ȣ��
	//0x8000 �������� �������� ���� ȣ��������� ��������
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		_keyDown.set(key, false);
	}
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp.set(key,true);
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp.set(key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)return true;
	return false;
}

bool KeyManager::IsToggleKey(int key)
{

	//GetKeyState :���� Ű�� ��ۻ���
	//0x0001������ �������� �ְ� ȣ��������� �ȴ��� ����

	if (GetKeyState(key) & 0x0001)return true;
	return false;
}
