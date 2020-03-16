#pragma once
#include "CommandBase.h"

class TransformDrone : public CommandBase
{
private:

	float birthX;
	float birthY;

public:
	TransformDrone();
	~TransformDrone();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void GetBirthXY(float X, float Y);
};

