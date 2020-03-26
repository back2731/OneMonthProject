#pragma once
#include "CommandBase.h"

class BuildExtractor : public CommandBase
{
private:

	int mutateX;
	int mutateY;

public:
	BuildExtractor();
	~BuildExtractor();

	void Update();

	void GetBirthXY(int X, int Y);
};

