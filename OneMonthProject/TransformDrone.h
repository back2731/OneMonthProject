#pragma once
#include "CommandBase.h"

class TransformDrone : public CommandBase
{
private:

	int birthX;
	int birthY;

public:
	TransformDrone();
	~TransformDrone();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void GetBirthXY(int X, int Y);
};

