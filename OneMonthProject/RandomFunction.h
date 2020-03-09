#pragma once
#include"SingletonBase.h"
class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction()
	{
		srand(GetTickCount());
	}
	~RandomFunction(){}

	//지정한 숫자범위내에서 난수를 받아온다.0~지정한 숫자
	inline int GetInt(int num)
	{
		return rand() % num;
	}
	inline int GetFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};
