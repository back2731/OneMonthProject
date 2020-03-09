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

	//한번만 눌렀냐
	bool IsOnceKeyDown(int key);
	//눌렀다가 뗏냐
	bool IsOnceKeyUp(int key);
	//누르고 있냐
	bool IsStayKeyDown(int key);
	//토글키냐
	bool IsToggleKey(int key);
};

