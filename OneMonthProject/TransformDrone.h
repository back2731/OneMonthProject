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

	void Update();

	void GetBirthXY(int X, int Y);

	void PayCost();
};

