#pragma once
#include"SingletonBase.h"
class TxtData :  public SingletonBase<TxtData>
{
public:
	TxtData();
	~TxtData();

	HRESULT Init();

	//���̺��
	void SaveTxt(char* saveFileName, vector<string>vStr);
	char* CombineVectorArray(vector<string> vArray);

	//�ε�

	vector<string>LoadTxt(char* loadFileName);
	vector<string>SeparateCharArray(char charArray[]);


};

