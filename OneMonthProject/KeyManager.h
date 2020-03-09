#pragma once
#include "SingletonBase.h"
#include <bitset>
using namespace std;
#define KEYMAX 256
class KeyManager :  public SingletonBase<KeyManager>
{
private:

	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
	
public:
	KeyManager();
	~KeyManager();

	HRESULT Init();

	void Release();

	//�ѹ��� ������
	bool IsOnceKeyDown(int key);
	//�����ٰ� �³�
	bool IsOnceKeyUp(int key);
	//������ �ֳ�
	bool IsStayKeyDown(int key);
	//���Ű��
	bool IsToggleKey(int key);
};

