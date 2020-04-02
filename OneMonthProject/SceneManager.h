#pragma once
#include "SingletonBase.h"

class GameNode;
class SceneManager :  public SingletonBase<SceneManager>
{
private:

	typedef map<string, GameNode*> mSceneList;
	typedef map<string, GameNode*>::iterator miSceneList;

private:
	//현재씬
	static GameNode* _currentScene;
	//목록
	mSceneList _mSceneList;

public:
	SceneManager();
	~SceneManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
	//씬추가하기
	GameNode* AddScene(string sceneName, GameNode* scene);

	HRESULT ChangeScene(string sceneName);
};

