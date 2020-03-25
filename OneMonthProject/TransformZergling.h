#pragma once
#include "CommandBase.h"

class TransformZergling : public CommandBase
{
private:

	int birthX;
	int birthY;

public:
	TransformZergling();
	~TransformZergling();

	void Update();

	void GetBirthXY(int X, int Y);

};

