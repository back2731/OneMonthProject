#pragma once
#include "CommandBase.h"

class LairRequires : public CommandBase
{
public:
	LairRequires();
	~LairRequires();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

