#pragma once
#include "BuildBase.h"

class Hatchery : public BuildBase
{
public:
	Hatchery();
	~Hatchery();

	Hatchery(int _playerNumber);


	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

