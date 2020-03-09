#pragma once
//=======================================
//SingletonBase(�̳༮���� �̱����� �����.)
//=======================================
/*
	�̱��� ������ static member�� �ϳ��� �ν��Ͻ���
	�����ȴ�. ���α׷� �ȿ��� ���������� ������ �����ϴ�.

	���������� �����ص� �ϳ��� �ν��Ͻ��� �����Ҽ� �ֱ� ������
	�̱��������� ����ϸ� Ŭ���� �ڽ��� �ڱ��� ������ �ν��Ͻ���
	�����ϴ� ����� ĸ��ȭ �Ͽ� ���� �Ҽ� �ִ�.
	���� ���, ��ü���� �� �Ҹ�, �ν��Ͻ� ���� ���� ����..
	Ȱ�뿡 �����ϴ�.

	�ڱ� �����ΰ� �ڱ��� ������ �ν��Ͻ��� �����ϴ�
	����� ��ü������ �����ϴ� ���� ����.
	�̳༮�� �ٸ� �ν��Ͻ��� �������� �ʵ��� ó���Ҽ� �ְ�
	���� ��� ���� ������ �Ѽ� �ִ�.
*/
template <typename T>
class SingletonBase
{
protected:
	//�̱��� �ν��Ͻ� �����ϱ�
	static T* singleton;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetSingleton();
	void ReleaseSingleton();

};

//�̱��� �ν��Ͻ� ����
template <typename T>
T* SingletonBase<T>::singleton = nullptr;

//�̱��� ��ü�� ��������
template<typename T>
T* SingletonBase<T>::GetSingleton()
{
	//�̱��� ��ü�� ������ ���� �����ڤ�.
	if (!singleton)singleton = new T;

	return singleton;
}
template<typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	//�̱��� ������ ����
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}


