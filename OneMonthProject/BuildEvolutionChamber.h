#pragma once
#include "CommandBase.h"

class BuildEvolutionChamber : public CommandBase
{
private:

	int mutateX;
	int mutateY;

public:
	BuildEvolutionChamber();
	~BuildEvolutionChamber();

	void Update();

	void GetBirthXY(int X, int Y);
};

