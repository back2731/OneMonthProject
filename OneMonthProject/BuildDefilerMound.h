#pragma once
#include "CommandBase.h"

class BuildDefilerMound : public CommandBase
{
private:

	int mutateX;
	int mutateY;

public:
	BuildDefilerMound();
	~BuildDefilerMound();

	void Update();

	void GetBirthXY(int X, int Y);
};

