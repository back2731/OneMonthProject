#pragma once
#include "CommandBase.h"

class TransformOverlord : public CommandBase
{
private:

	int birthX;
	int birthY;

public:
	TransformOverlord();
	~TransformOverlord();

	void Update();

	void GetBirthXY(int X, int Y);

};

