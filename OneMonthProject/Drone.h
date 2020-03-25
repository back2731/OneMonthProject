#pragma once
#include "UnitBase.h"
#include "Gathering.h"
#include "BaseBuilding.h"
#include "HighBuilding.h"

#include "BuildHatchery.h"
#include "BuildSpawningPool.h"

#define BUILDINGTILEMAX 16

struct MUTATERECT
{
	RECT			buildRect[BUILDINGTILEMAX];
	bool			choiceColor[BUILDINGTILEMAX];
};

class Drone : public UnitBase
{
private:
	CommandBase*	baseBuildingSlot[COMMANDMAX];
	CommandBase*	highBuildingSlot[COMMANDMAX];

	Image*			baseBuildingImage[COMMANDMAX];
	Image*			highBuildingImage[COMMANDMAX];

	bool			baseUIrender;
	bool			baseBuildingUIrender;
	bool			highBuildingUIrender;

	bool			mutateState;

	Image*			greenRectImage;
	Image*			redRectImage;
	MUTATERECT		mutateRect;
	
	RECT			buildRectRender;
	bool			isPossible;

	bool			isTransHatchery;
	bool			isArriveHatchery;
	bool			mutateHatchery;
	Image*			mutateHatcheryImage;

	bool			isTransSpawningPool;
	bool			isArriveSpawningPool;
	bool			mutateSpawningPool;
	Image*			mutateSpawningPoolImage;

	RECT			temp;



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

