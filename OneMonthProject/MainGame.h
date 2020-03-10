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

	virtual HRESULT Init();	//�ʱ�ȭ
	virtual void Release();	//����
	virtual void Update();	//�����ϴ°�
	virtual void Render();	//�׸��°�
};