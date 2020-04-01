#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	Image*	titleImage;
	int		loadingCount;

public:
	TitleScene();
	~TitleScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

