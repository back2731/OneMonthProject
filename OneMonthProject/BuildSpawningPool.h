#pragma once
#include "CommandBase.h"

class BuildSpawningPool : public CommandBase
{
private:

	int mutateX;
	int mutateY;

public:
	BuildSpawningPool();
	~BuildSpawningPool();

	void Update();

	void GetBirthXY(int X, int Y);
};

