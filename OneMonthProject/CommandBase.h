#pragma once
#define COMMANDMAX 9

class CommandBase
{
private:
	
public:
	CommandBase();
	~CommandBase();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

};

