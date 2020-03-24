#pragma once
#include "CommandBase.h"

class BuildHatchery : public CommandBase
{
private:

	int mutateX;
	int mutateY;

public:
	BuildHatchery();
	~BuildHatchery();

	void Update();

	void GetBirthXY(int X, int Y);

};

