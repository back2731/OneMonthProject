#pragma once
#include "GameNode.h"
class MenuScene : public GameNode
{
private:
	Image*	backGroundImage;
	
	Image*	singlePlay;
	Image*	singlePlayOverlay;
	RECT	singlePlayRect;
	RECT	singlePlayOverlayRect;

	int		singlePlayframeCount;
	int		singlePlayframeIndexX;
	int		singlePlayframeIndexY;

	int		singlePlayOverlayframeCount;
	int		singlePlayOverlayframeIndexX;
	int		singlePlayOverlayframeIndexY;


	Image*	mapTool;
	Image*	mapToolOverlay;
	RECT	mapToolRect;
	RECT	mapToolOverlayRect;

	int		mapToolframeCount;
	int		mapToolframeIndexX;
	int		mapToolframeIndexY;

	int		mapToolOverlayframeCount;
	int		mapToolOverlayframeIndexX;
	int		mapToolOverlayframeIndexY;

	Image*	exit;
	Image*	exitOverlay;
	RECT	exitRect;
	RECT	exitOverlayRect;

	int		exitframeCount;
	int		exitframeIndexX;
	int		exitframeIndexY;

	int		exitOverlayframeCount;
	int		exitOverlayframeIndexX;
	int		exitOverlayframeIndexY;

public:
	MenuScene();
	~MenuScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

