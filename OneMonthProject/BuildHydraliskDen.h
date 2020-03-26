#pragma once
#include "CommandBase.h"

class BuildHydraliskDen : public CommandBase
{

private:

	int mutateX;
	int mutateY;

public:
	BuildHydraliskDen();
	~BuildHydraliskDen();

	void Update();

	void GetBirthXY(int X, int Y);

};

