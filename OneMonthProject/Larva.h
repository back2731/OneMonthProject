#pragma once
#include "UnitBase.h"
#include "TransformDrone.h"
#include "TransformZergling.h"
#include "TransformOverlord.h"
#include "TransformHydralisk.h"
#include "TransformMutalisk.h"
#include "TransformScourge.h"
#include "TransformQueen.h"
#include "TransformUltralisk.h"
#include "TransformDefiler.h"

class Larva : public UnitBase
{
private:

	int hatcheryX;
	int hatcheryY;

	int larvaNumber;

	int test;

	int rndNum;
public:
	Larva();
	~Larva();

	Larva(int _playerNumber, POINT birthXY, int _hatcheryX, int _hatcheryY, int _larvaNumber);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void RenderUI(HDC hdc) override;

	int GetHatcheryX() { return hatcheryX; }
	int GetHatcheryY() { return hatcheryY; }
	int GetLarvaNumber() { return larvaNumber; }

	void PlayAnimation();

};

