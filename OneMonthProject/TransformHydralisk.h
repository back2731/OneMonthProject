#pragma once
#include "CommandBase.h"

class TransformHydralisk : public CommandBase
{
private:

	int birthX;
	int birthY;

public:
	TransformHydralisk();
	~TransformHydralisk();

	void Update();

	void GetBirthXY(int X, int Y);

};

