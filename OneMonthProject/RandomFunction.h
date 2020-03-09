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

	//������ ���ڹ��������� ������ �޾ƿ´�.0~������ ����
	inline int GetInt(int num)
	{
		return rand() % num;
	}
	inline int GetFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};
