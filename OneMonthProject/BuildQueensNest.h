#pragma once
#include "CommandBase.h"

class BuildQueensNest : public CommandBase
{
private:

	int mutateX;
	int mutateY;

public:
	BuildQueensNest();
	~BuildQueensNest();

	void Update();

	void GetBirthXY(int X, int Y);
};

