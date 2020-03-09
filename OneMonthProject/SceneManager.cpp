#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}
//������� �ΰ����� �ʱ�ȭ ����.
GameNode* SceneManager::_currentScene = nullptr;
HRESULT SceneManager::Init()
{
	return S_OK;
}

void SceneManager::Release()
{
	miSceneList iter = _mSceneList.begin();
	for (iter; iter != _mSceneList.end();)
	{
		//����
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene)iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	_mSceneList.clear();
}

void SceneManager::Update()
{
	if (_currentScene)
	{
		_currentScene->Update();
	}
}

void SceneManager::Render()
{
	if (_currentScene)_currentScene->Render();
}

GameNode * SceneManager::AddScene(string sceneName, GameNode * scene)
{

	if(!scene)return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return nullptr;

}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã���� E_FAIL
	if (find == _mSceneList.end())return E_FAIL;

	//�ٲٷ��¾��� ������̶� ���Ƶ� E_FAIL
	if (find->second == _currentScene)return E_FAIL;

	//������� �Դٸ� ������ ���� �� ���� �ʱ�ȭ�ϰ� ��������.
	if (SUCCEEDED(find->second->Init()))
	{
		//Ȥ�� ������ ���� �ִٸ� ������
		if (_currentScene)_currentScene->Release();

		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}
