#pragma once
#include "SingletonBase.h"
#include "EvolveBurrow.h"
#include "LairRequires.h"
#include "SelectLarva.h"
#include "SetRallyPoint.h"

#define COMMANDMAX 9

class CommandManager : public SingletonBase<CommandManager>
{
private:
	CommandBase*	hatcheryCommand[COMMANDMAX];
	RECT			commandSlot[COMMANDMAX];
public:
	CommandManager();
	~CommandManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

