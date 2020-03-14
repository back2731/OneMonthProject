#pragma once
#include "SingletonBase.h"
#include "EvolveBurrow.h"
#include "LairRequires.h"
#include "SelectLarva.h"
#include "SetRallyPoint.h"

class CommandManager : public SingletonBase<CommandManager>
{
private:

public:
	CommandManager();
	~CommandManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

