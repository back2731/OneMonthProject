#pragma once
#include "CommandBase.h"

class TransformDefiler : public CommandBase
{
private:

	int birthX;
	int birthY;

public:
	TransformDefiler();
	~TransformDefiler();

	void Update();

	void GetBirthXY(int X, int Y);

};

