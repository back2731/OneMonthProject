#pragma once
#include "CommandBase.h"

class TransformUltralisk : public CommandBase
{
private:

	int birthX;
	int birthY;

public:
	TransformUltralisk();
	~TransformUltralisk();

	void Update();

	void GetBirthXY(int X, int Y);

};

