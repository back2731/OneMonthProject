#pragma once
#include "GameNode.h"
#include "GameScene.h"
#include "AStarScene.h"
#include "MapToolScene.h"

class MainGame :  public GameNode
{
private:

public:
	MainGame();
	~MainGame();

	virtual HRESULT Init();	//초기화
	virtual void Release();	//해제
	virtual void Update();	//연산하는곳
	virtual void Render();	//그리는곳
};