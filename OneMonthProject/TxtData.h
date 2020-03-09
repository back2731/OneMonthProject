#pragma once
#include"SingletonBase.h"
class TxtData :  public SingletonBase<TxtData>
{
public:
	TxtData();
	~TxtData();

	HRESULT Init();

	//세이브용
	void SaveTxt(char* saveFileName, vector<string>vStr);
	char* CombineVectorArray(vector<string> vArray);

	//로드

	vector<string>LoadTxt(char* loadFileName);
	vector<string>SeparateCharArray(char charArray[]);


};

