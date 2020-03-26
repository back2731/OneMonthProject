#pragma once
#include "UnitBase.h"
#include "Gathering.h"
#include "BaseBuilding.h"
#include "HighBuilding.h"

#include "BuildHatchery.h"
#include "BuildSpawningPool.h"
#include "BuildHydraliskDen.h"
#include "BuildEvolutionChamber.h"
#include "BuildCreepColony.h"
#include "BuildExtractor.h"
#include "BuildSpire.h"
#include "BuildQueensNest.h"

#define BUILDINGTILEMAX 16
#define ALPHA 75

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

	bool			isTransHydraliskDen;
	bool			isArriveHydraliskDen;
	bool			mutateHydraliskDen;
	Image*			mutateHydraliskDenImage;

	bool			isTransEvolutionChamber;
	bool			isArriveEvolutionChamber;
	bool			mutateEvolutionChamber;
	Image*			mutateEvolutionChamberImage;

	bool			isTransCreepColony;
	bool			isArriveCreepColony;
	bool			mutateCreepColony;
	Image*			mutateCreepColonyImage;

	bool			isTransExtractor;
	bool			isArriveExtractor;
	bool			mutateExtractor;
	Image*			mutateExtractorImage;

	bool			isTransSpire;
	bool			isArriveSpire;
	bool			mutateSpire;
	Image*			mutateSpireImage;

	bool			isTransQueensNest;
	bool			isArriveQueensNest;
	bool			mutateQueensNest;
	Image*			mutateQueensNestImage;

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
	bool CheckMutate();
};

