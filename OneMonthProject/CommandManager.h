#pragma once
#include "SingletonBase.h"
#include "AttackCommand.h"
#include "HoldCommand.h"
#include "MoveCommand.h"
#include "StopCommand.h"
#include "PauseCommand.h"
#include "PatrolCommand.h"
#include "Burrow.h"

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

