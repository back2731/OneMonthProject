#pragma once
#include "CommandBase.h"

class BuildSpire : public CommandBase
{
private:

	int mutateX;
	int mutateY;

public:
	BuildSpire();
	~BuildSpire();

	void Update();

	void GetBirthXY(int X, int Y);
};

