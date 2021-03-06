#pragma once
#include "GameNode.h"
#include "ResourceCollection.h"
#include "GameScene.h"
#include "MapToolScene.h"
#include "TitleScene.h"
#include "MenuScene.h"

class MainGame :  public GameNode
{
private:
	MapToolScene* map;
	ResourceCollection* resource;

public:
	MainGame();
	~MainGame();

	virtual HRESULT Init();	//초기화
	virtual void Release();	//해제
	virtual void Update();	//연산하는곳
	virtual void Render();	//그리는곳
};