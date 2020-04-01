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

	virtual HRESULT Init();	//�ʱ�ȭ
	virtual void Release();	//����
	virtual void Update();	//�����ϴ°�
	virtual void Render();	//�׸��°�
};