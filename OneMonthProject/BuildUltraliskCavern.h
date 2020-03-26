#pragma once
#include "CommandBase.h"

class BuildUltraliskCavern : public CommandBase
{
private:

	int mutateX;
	int mutateY;

public:
	BuildUltraliskCavern();
	~BuildUltraliskCavern();

	void Update();

	void GetBirthXY(int X, int Y);
};

