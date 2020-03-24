#pragma once
#include "UnitBase.h"
#include "Gathering.h"
#include "BaseBuilding.h"
#include "HighBuilding.h"
#define BUILDINGTILEMAX 16

struct MUTATERECT
{
	RECT			buildRect[BUILDINGTILEMAX];
	bool			choiceColor[BUILDINGTILEMAX];
};

class Drone : public UnitBase
{
private:
	Image*			baseBuildingImage[COMMANDMAX];
	Image*			highBuildingImage[COMMANDMAX];

	bool			baseUIrender;
	bool			baseBuildingUIrender;
	bool			highBuildingUIrender;

	bool			mutateState;

	Image*			greenRectImage;
	Image*			redRectImage;
	MUTATERECT		mutateRect;

	int				saveUnitPosition;
	
	RECT			buildRectRender;
	bool			isPossible;

	bool			mutateHatchery;
	Image*			mutateHatcheryImage;

	RECT			temp;

	bool			isTransHatchery;


public:
	Drone();
	~Drone();
	Drone(int _playerNumber, POINT birthXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void RenderUI(HDC hdc) override;

	void PlayAnimation();

	bool CheckCollision();
};

