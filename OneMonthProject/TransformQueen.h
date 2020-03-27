#pragma once
#include "CommandBase.h"

class TransformQueen : public CommandBase
{
private:

	int birthX;
	int birthY;
	
public:
	TransformQueen();
	~TransformQueen();

	void Update();

	void GetBirthXY(int X, int Y);
};

