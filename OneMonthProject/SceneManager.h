#pragma once
#include "SingletonBase.h"

class GameNode;
class SceneManager :  public SingletonBase<SceneManager>
{
private:

	typedef map<string, GameNode*> mSceneList;
	typedef map<string, GameNode*>::iterator miSceneList;

private:
	//�����
	static GameNode* _currentScene;
	//���
	mSceneList _mSceneList;

public:
	SceneManager();
	~SceneManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
	//���߰��ϱ�
	GameNode* AddScene(string sceneName, GameNode* scene);

	HRESULT ChangeScene(string sceneName);
};

