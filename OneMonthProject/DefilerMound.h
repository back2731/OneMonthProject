#pragma once
#include "BuildBase.h"

class DefilerMound : public BuildBase
{
public:
	DefilerMound();
	~DefilerMound();
	
	DefilerMound(int _playerNumber, POINT buildXY);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void RenderUI(HDC hdc) override;
};

