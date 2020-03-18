#pragma once
#include "SingletonBase.h"

class UIManager : public SingletonBase<UIManager>
{

public:
	UIManager();
	~UIManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

