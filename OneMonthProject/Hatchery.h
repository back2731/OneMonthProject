#pragma once
#include "BuildBase.h"

class Hatchery : public BuildBase
{
	int frameCount;
	int frameIndex;

public:
	Hatchery();
	~Hatchery();

	Hatchery(int _playerNumber, POINT buildXY);


	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

