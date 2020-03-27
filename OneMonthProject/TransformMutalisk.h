#pragma once
#include "CommandBase.h"

class TransformMutalisk : public CommandBase
{
private:

	int birthX;
	int birthY;

public:
	TransformMutalisk();
	~TransformMutalisk();

	void Update();

	void GetBirthXY(int X, int Y);
};

