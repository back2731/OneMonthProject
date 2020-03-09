#include "stdafx.h"
#include "TxtData.h"
#pragma warning(disable : 4996)

TxtData::TxtData()
{
}
TxtData::~TxtData()
{
}

HRESULT TxtData::Init()
{
	return S_OK;
}
//����¥�� �����͸� ��ƵѰ�(��� �����͸� ���� ������ ©�� �����Ѵ�.)
void TxtData::SaveTxt(char * saveFileName, vector<string> vStr)
{

	HANDLE file;
	char str[128];
	DWORD write;


	strncpy_s(str, 128, CombineVectorArray(vStr), 128);


	file = CreateFile
	(saveFileName,			//������ ���϶Ǵ� �� ��ġ�� �����̸�
		GENERIC_WRITE,		//�����̳� ��ġ�� ����ų� ���� ����� ����
		0,					//���� ���� ����Է�
		NULL,				//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
		CREATE_ALWAYS,		//�����̳� ��ġ�� ���� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL, //�����̳� ��ġ�� ���� ���� �� Ư��
		NULL);				//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);

}
//���� ����� ������(����¥�� �����͸� ��ǥ ������ �� ����)
char * TxtData::CombineVectorArray(vector<string> vArray)
{
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 128, vArray[i].c_str(), 128);

		if ((i + 1) < vArray.size())
		{
			strcat(str, ",");
		}
	}
	return str;
}

vector<string> TxtData::LoadTxt(char * loadFileName)
{
	HANDLE file;
	char str[128];
	DWORD read;

	file = CreateFile
	(loadFileName,			//������ ���϶Ǵ� �� ��ġ�� �����̸�
		GENERIC_READ,		//�����̳� ��ġ�� ����ų� ���� ����� ����
		0,					//���� ���� ����Է�
		NULL,				//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
		OPEN_EXISTING,		//�����̳� ��ġ�� ���� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL, //�����̳� ��ġ�� ���� ���� �� Ư��
		NULL);				//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

	ReadFile(file, str, 128, &read, NULL);
	CloseHandle(file);
	return SeparateCharArray(str);
}
vector<string> TxtData::SeparateCharArray(char charArray[])
{
	vector<string>vArray;

	char* seperator = ",";
	char* token;

	token = strtok(charArray, seperator);
	vArray.push_back(token);

	while (NULL!=(token = strtok(NULL, seperator)))
	{
		vArray.push_back(token);
	}
	return vArray;
}
