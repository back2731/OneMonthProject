#pragma once
#include "CommandBase.h"

class BuildCreepColony : public CommandBase
{
private:

	int mutateX;
	int mutateY;

public:
	BuildCreepColony();
	~BuildCreepColony();

	void Update();

	void GetBirthXY(int X, int Y);
};

