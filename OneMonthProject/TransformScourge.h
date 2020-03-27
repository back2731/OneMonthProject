#pragma once
#include "CommandBase.h"

class TransformScourge : public CommandBase
{
private:

	int birthX;
	int birthY;

public:
	TransformScourge();
	~TransformScourge();

	void Update();

	void GetBirthXY(int X, int Y);
};

